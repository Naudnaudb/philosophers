/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                         	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abordack <abordack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:09:19 by abordack          #+#    #+#             */
/*   Updated: 2021/09/28 18:09:21 by abordack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	if_is_dead(t_env *env, t_philo *philo)
{
	int	i;

	while (!(env->all_ate))
	{
		i = -1;
		while (++i < env->nb_philo && !(env->dieded))
		{
			pthread_mutex_lock(&(env->meal_check));
			if (time_diff(philo[i].last_meal, time_in_ms()) > env->time_to_die)
			{
				philo_print(env, i, "died");
				env->dieded = 1;
			}
			pthread_mutex_unlock(&(env->meal_check));
			usleep(100);
		}
		if (env->dieded)
			break ;
		i = 0;
		while (env->nb_eat != -1 && i < env->nb_philo && \
			  philo[i].nb_of_eat >= env->nb_eat)
			i++;
		if (i == env->nb_philo)
			env->all_ate = 1;
	}
}

void	exit_prog(t_env *env, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	free(env->philos);
	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_destroy(&(env->forks[i]));
		i++;
	}
	free(env->forks);
	pthread_mutex_destroy(&(env->writing));
}

void	eat(t_philo *philo)
{
	t_env	*env;

	env = philo->env;
	pthread_mutex_lock(&(env->forks[philo->left]));
	philo_print(env, philo->id, "has taken a fork");
	pthread_mutex_lock(&(env->forks[philo->right]));
	philo_print(env, philo->id, "has taken a fork");
	pthread_mutex_lock(&(env->meal_check));
	philo_print(env, philo->id, "is eating");
	philo->last_meal = time_in_ms();
	pthread_mutex_unlock(&(env->meal_check));
	smart_sleep(env->time_to_eat, env);
	(philo->nb_of_eat)++;
	pthread_mutex_unlock(&(env->forks[philo->left]));
	pthread_mutex_unlock(&(env->forks[philo->right]));
}

void	*start_routine(void *void_philosopher)
{
	int		i;
	t_philo	*philo;
	t_env	*env;

	i = 0;
	philo = (t_philo *)void_philosopher;
	env = philo->env;
	if (philo->id % 2)
		usleep(15000);
	while (!(env->dieded))
	{
		eat(philo);
		if (env->all_ate)
			break ;
		philo_print(env, philo->id, "is sleeping");
		smart_sleep(env->time_to_sleep, env);
		philo_print(env, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

int	prog(t_env *env)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = env->philos;
	env->launch_time = time_in_ms();
	while (i < env->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, start_routine, &(phi[i])))
			return (1);
		phi[i].last_meal = time_in_ms();
		i++;
	}
	if_is_dead(env, env->philos);
	exit_prog(env, phi);
	return (0);
}
