/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:46 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/17 12:14:47 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define PHILO_LIMIT 250
# define INVALID_PHILO_COUNT "Invalid number of philosophers"
# define INVALID_TIME_TO_DIE "Invalid time to die"
# define INVALID_TIME_TO_EAT "Invalid time to eat"
# define INVALID_TIME_TO_SLEEP " Invalid time to sleep"
# define INVALID_TIMES_TO_EAT "Invalid number of times to eat"
# define INVALID_ARGS "Invalid number of arguments"
# define THREAD_CREATE_FAIL "Thread creation failed"
# define THREAD_JOIN_FAIL "Thread join failed"

typedef int	t_bool;

struct		s_main;

typedef struct s_philo
{
	struct s_main	*m;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_lock;
	pthread_t		thread;
	size_t			last_meal;
	int				times_eaten;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	pthread_t		overseer;
	pthread_mutex_t	*forks;
	t_bool			dead_philo;
	pthread_mutex_t	dead_lock;
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
void	*routine(void *ptr);
void	*overseer(void *ptr);
void	error_exit(char *msg);
size_t	get_time(void);
void	threads(t_main *m);
int		destroy_mutexes(t_main *m, char *msg);

// UTILS
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	ft_sleep(size_t time);

#endif