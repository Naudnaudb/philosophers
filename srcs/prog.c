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

void	eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&(info->forks[philo->left]));
	action_print(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&(info->forks[philo->right]));
	action_print(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&(info->meal_check));
	action_print(info, philo->id, "is eating");
	philo->last_meal = time_in_ms();
	pthread_mutex_unlock(&(info->meal_check));
	smart_sleep(info->time_to_eat, info);
	(philo->nb_of_eat)++;
	pthread_mutex_unlock(&(info->forks[philo->left]));
	pthread_mutex_unlock(&(info->forks[philo->right]));
}

void	*p_thread(void *void_philosopher)
{
	int		i;
	t_philo	*philo;
	t_info	*info;

	i = 0;
	philo = (t_philo *)void_philosopher;
	info = philo->info;
	if (philo->id % 2)
		usleep(15000);
	while (!(info->dieded))
	{
		eat(philo);
		if (info->all_ate)
			break ;
		action_print(info, philo->id, "is sleeping");
		smart_sleep(info->time_to_sleep, info);
		action_print(info, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_prog(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->writing));
}

void	if_is_dead(t_info *info, t_philo *philo)
{
	int	i;

	while (!(info->all_ate))
	{
		i = -1;
		while (++i < info->nb_philo && !(info->dieded))
		{
			pthread_mutex_lock(&(info->meal_check));
			if (time_diff(philo[i].last_meal, time_in_ms()) > info->time_to_die)
			{
				action_print(info, i, "died");
				info->dieded = 1;
			}
			pthread_mutex_unlock(&(info->meal_check));
			usleep(100);
		}
		if (info->dieded)
			break ;
		i = 0;
		while (info->nb_eat != -1 && i < info->nb_philo && \
				philo[i].nb_of_eat >= info->nb_eat)
			i++;
		if (i == info->nb_philo)
			info->all_ate = 1;
	}
}

int	prog(t_info *info)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = info->philos;
	info->launch_time = time_in_ms();
	while (i < info->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].last_meal = time_in_ms();
		i++;
	}
	if_is_dead(info, info->philos);
	exit_prog(info, phi);
	return (0);
}
