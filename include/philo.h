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
	long long			last_meal;
	pthread_t			thread_id;
	struct s_env		*env;
}				t_philo;

typedef struct s_env
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
	pthread_mutex_t		writing;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}				t_env;

int						error(char *str);
int						ft_malloc(void *dst, size_t size);
int						init(t_env *env, char **av);
void					philo_print(t_env *env, int id, char *str);
void					smart_sleep(long long time, t_env *env);
int						prog(t_env *env);
void					exit_prog(t_env *env, t_philo *philos);
long long				time_in_ms(void);
long long				time_diff(long long past, long long pres);
int						ft_atoi(const char *str);

#endif
