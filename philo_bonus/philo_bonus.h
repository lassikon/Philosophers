/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:12 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/24 11:46:24 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

# define PHILO_LIMIT 200

# define PHILO_COUNT_ERR "Error: Invalid number of philosophers\n"
# define TIME_TO_DIE_ERR "Error: Invalid time to die\n"
# define TIME_TO_EAT_ERR "Error: Invalid time to eat\n"
# define TIME_TO_SLEEP_ERR "Error: Invalid time to sleep\n"
# define TIMES_TO_EAT_ERR "Error: Invalid number of times to eat\n"
# define ARG_COUNT_ERR "Error: Invalid number of arguments\n"
# define GET_TIME_ERR "Error: gettimeoftheday failed\n"
# define FORK_ERR "Error: Fork failed\n"
# define SEM_ERR "Error: Semaphore initialization failed\n"
# define THREAD_CREATE_ERR "Error: Thread creation failed\n"

struct	s_main;

typedef struct s_philo
{
	int				id;
	size_t			last_meal;
	size_t			times_eaten;
	pthread_t		monitor;
	struct s_main	*m;
}	t_philo;

typedef struct s_main
{
	int		pid[PHILO_LIMIT];
	int		philo_count;
	int		death_monitor_pid;
	int		eat_monitor_pid;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_to_eat;
	size_t	start_time;
	sem_t	*forks;
	sem_t	*output;
	sem_t	*finished;
	sem_t	*dead;
	sem_t	*eat;
}	t_main;

void	init(t_main *m, int argc, char **argv);
void	fork_philos(t_main *m);
void	fork_monitors(t_main *m);
void	wait_monitors(t_main *m);
void	close_semaphores(t_main *m);
void	kill_philos(t_main *m, int i);
int		invalid_args(int argc, char **argv);
int		get_number(const char *str);
size_t	get_time(void);
void	ft_sleep(size_t time);
int		ft_strlen(char *str);
void	output_msg(t_main *m, t_philo *philo, char *msg);

#endif