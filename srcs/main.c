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

int	init_mutex(t_info *info)
{
	int	i;

	i = info->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(info->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(info->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	i = info->nb_philo - 1;
	while (i >= 0)
	{
		info->philos[i].id = i;
		info->philos[i].nb_of_eat = 0;
		info->philos[i].left = i;
		info->philos[i].right = (i + 1) % info->nb_philo;
		info->philos[i].last_meal = 0;
		info->philos[i].info = info;
		i--;
	}
	return (0);
}

void	check_info(t_info *info)
{
	if (info->nb_philo < 2)
		error("Not enough of philosophers");
	if (info->time_to_die < 0)
		error("The arg time_to_die must be positive");
	if (info->time_to_eat < 0)
		error("The arg time_to_eat must be positive");
	if (info->time_to_sleep < 0)
		error("The arg time_to_sleep must be positive");
}

int	init_all(t_info *info, char **av)
{
	info->nb_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->all_ate = 0;
	info->dieded = 0;
	check_info(info);
	if (av[5])
	{
		info->nb_eat = ft_atoi(av[5]);
		if (info->nb_eat <= 0)
			error("The arg nb_eat must be strictly positive");
	}
	else
		info->nb_eat = -1;
	if (init_mutex(info))
		return (2);
	init_philos(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
		return (printf("Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"));
	init_all(&info, av);
	if (prog(&info))
		return (printf("Error:\nCan't create the threads"));
	return (0);
}
