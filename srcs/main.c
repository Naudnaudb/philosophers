/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abordack <abordack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:09:23 by abordack          #+#    #+#             */
/*   Updated: 2021/09/28 18:09:24 by abordack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	mutex_init(t_env *env)
{
	int	i;

	i = env->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(env->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(env->meal_check), NULL))
		return (1);
	return (0);
}

int	philos_init(t_env *env)
{
	int	i;

	i = env->nb_philo - 1;
	while (i >= 0)
	{
		env->philos[i].id = i;
		env->philos[i].nb_of_eat = 0;
		env->philos[i].left = i;
		env->philos[i].right = (i + 1) % env->nb_philo;
		env->philos[i].last_meal = 0;
		env->philos[i].env = env;
		i--;
	}
	return (0);
}

void	check_arg(t_env *env)
{
	if (env->nb_philo < 2)
		error("Not enough of philosophers");
	if (env->time_to_die < 0)
		error("The arg time_to_die must be positive");
	if (env->time_to_eat < 0)
		error("The arg time_to_eat must be positive");
	if (env->time_to_sleep < 0)
		error("The arg time_to_sleep must be positive");
}

int	init(t_env *env, char **av)
{
	env->nb_philo = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	env->all_ate = 0;
	env->dieded = 0;
	check_arg(env);
	if (av[5])
	{
		env->nb_eat = ft_atoi(av[5]);
		if (env->nb_eat <= 0)
			error("The arg nb_eat must be strictly positive");
	}
	else
		env->nb_eat = -1;
	if (ft_malloc(&env->philos, sizeof(t_philo) * env->nb_philo) || \
		ft_malloc(&env->forks, sizeof(pthread_mutex_t) * env->nb_philo))
		return (error("malloc failed"));
	if (mutex_init(env))
		return (2);
	philos_init(env);
	return (0);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (ac != 5 && ac != 6)
		return (printf("Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"));
	init(&env, av);
	if (prog(&env))
		return (printf("Error:\nCan't create the threads"));
	return (0);
}
