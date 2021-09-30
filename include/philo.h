/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abordack <abordack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:08:56 by abordack          #+#    #+#             */
/*   Updated: 2021/09/28 18:09:00 by abordack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					nb_of_eat;
	int					left;
	int					right;
	long long			t_last_meal;
	pthread_t			thread_id;
	struct s_info		*info;
}				t_philo;

typedef struct s_info
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			launch_time;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philo				philos[250];
}				t_info;

/*
** ----- error_manager.c -----
*/

int						error(char *str);
int						error_manager(int error);

/*
** ----- init.c -----
*/

int						init_all(t_info *info, char **av);

/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
void					action_print(t_info *info, int id, char *string);
long long				time_in_ms(void);
long long				time_diff(long long past, long long pres);
void					smart_sleep(long long time, t_info *info);

/*
** ----- launcher.c -----
*/

int						prog(t_info *info);
void					exit_prog(t_info *info, t_philo *philos);

#endif
