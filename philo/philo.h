/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:46 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/25 11:04:21 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define PHILO_LIMIT 200

# define PHILO_COUNT_ERR "Error: Invalid number of philosophers\n"
# define TIME_TO_DIE_ERR "Error: Invalid time to die\n"
# define TIME_TO_EAT_ERR "Error: Invalid time to eat\n"
# define TIME_TO_SLEEP_ERR "Error: Invalid time to sleep\n"
# define TIMES_TO_EAT_ERR "Error: Invalid number of times to eat\n"
# define ARG_COUNT_ERR "Error: Invalid number of arguments\n"
# define GET_TIME_ERR "Error: gettimeoftheday failed\n"
# define THREAD_CREATE_ERR "Error: Thread creation failed\n"
# define THREAD_JOIN_ERR "Error: Thread join failed\n"

# define TRUE 1
# define FALSE 0

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
	size_t			times_eaten;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	pthread_t		overseer;
	pthread_mutex_t	*forks;
	t_bool			dead_philo;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	output_lock;
	int				philo_count;
	int				threads_created;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			times_to_eat;
	size_t			start_time;
}	t_main;

int		init(t_main *m, int argc, char **argv);
int		invalid_args(int argc, char **argv);
void	*routine(void *ptr);
void	*overseer(void *ptr);
size_t	get_time(void);
int		threads(t_main *m);
int		get_number(const char *str);
int		ft_strlen(char *str);
void	ft_sleep(size_t time);

#endif