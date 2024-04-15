/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:46 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 16:21:46 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define true 1
# define false 0
# define PHILO_LIMIT 200
# define INVALID_PHILO_COUNT "Error: Invalid number of philosophers"

typedef int	t_bool;

typedef struct s_philo
{
	int				id;
	t_bool			eating;
	t_bool			*dead_philo;
	pthread_mutex_t	*output_lock;
	pthread_mutex_t	*time_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal;
	size_t			times_eaten;
	size_t			start_time;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	pthread_t		overseer;
	pthread_mutex_t	*forks;
	t_bool			error;
	t_bool			dead_philo;
	pthread_mutex_t dead_lock;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	time_lock;
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				times_to_eat;
	size_t			start_time;
}	t_main;

void	init(t_main *m, int argc, char **argv);
int		invalid_args(int argc, char **argv);
void	*routine(t_philo philo);
void	*overseer(void *ptr);
void	error_exit(char *msg);
size_t	get_time();

// UTILS
int	ft_atoi(const char *str);
int	ft_strlen(char *str);

#endif