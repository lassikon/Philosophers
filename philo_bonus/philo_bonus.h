/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:12 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/18 14:17:17 by lkonttin         ###   ########.fr       */
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

# define PHILO_LIMIT 250

# define PHILO_COUNT_ERR "Error: Invalid number of philosophers\n"
# define TIME_TO_DIE_ERR "Error: Invalid time to die\n"
# define TIME_TO_EAT_ERR "Error: Invalid time to eat\n"
# define TIME_TO_SLEEP_ERR "Error: Invalid time to sleep\n"
# define TIMES_TO_EAT_ERR "Error: Invalid number of times to eat\n"
# define ARG_COUNT_ERR "Error: Invalid number of arguments\n"
# define GET_TIME_ERR "Error: gettimeoftheday failed\n"
# define FORK_ERR "Error: Fork failed\n"
# define SEM_ERR "Error: Semaphore initialization failed\n"

typedef struct s_philo
{
	int		id;
	size_t	last_meal;
	int		times_eaten;
}	t_philo;

typedef struct s_main
{
	int		pid[PHILO_LIMIT];
	int		philo_count;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_to_eat;
	size_t	start_time;
	sem_t	*forks;
	sem_t	*output;
	sem_t	*finished;
}	t_main;

void	init(t_main *m, int argc, char **argv);
void	forks(t_main *m);
int		invalid_args(int argc, char **argv);
int		ft_atoi(const char *str);
size_t	get_time(void);
void	ft_sleep(size_t time);
int		ft_strlen(char *str);
void	output_msg(t_main *m, t_philo *philo, char *msg);

#endif