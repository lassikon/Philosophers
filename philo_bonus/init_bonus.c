/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:48 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/24 12:00:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	not_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	invalid_args(int argc, char **argv)
{
	if (not_digit(argv[1]) || get_number(argv[1]) < 1
		|| get_number(argv[1]) > PHILO_LIMIT)
		return (write(2, PHILO_COUNT_ERR, ft_strlen(PHILO_COUNT_ERR)));
	if (not_digit(argv[2]) || get_number(argv[2]) < 1)
		return (write(2, TIME_TO_DIE_ERR, ft_strlen(TIME_TO_DIE_ERR)));
	if (not_digit(argv[3]) || get_number(argv[3]) < 1)
		return (write(2, TIME_TO_EAT_ERR, ft_strlen(TIME_TO_EAT_ERR)));
	if (not_digit(argv[4]) || get_number(argv[4]) < 1)
		return (write(2, TIME_TO_SLEEP_ERR, ft_strlen(TIME_TO_SLEEP_ERR)));
	if (argc == 6)
		if (not_digit(argv[5]) || get_number(argv[5]) < 0)
			return (write(2, TIMES_TO_EAT_ERR, ft_strlen(TIMES_TO_EAT_ERR)));
	return (0);
}

static void	open_semaphores(t_main *m)
{
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("finished");
	sem_unlink("dead");
	sem_unlink("eat");
	m->forks = sem_open("forks", O_CREAT, 0600, m->philo_count);
	m->output = sem_open("output", O_CREAT, 0600, 1);
	m->finished = sem_open("finished", O_CREAT, 0600, m->philo_count);
	m->dead = sem_open("dead", O_CREAT, 0600, m->philo_count);
	m->eat = sem_open("eat", O_CREAT, 0600, 1);
	if (m->forks == SEM_FAILED || m->output == SEM_FAILED
		|| m->finished == SEM_FAILED || m->dead == SEM_FAILED
		|| m->eat == SEM_FAILED)
	{
		write(2, SEM_ERR, ft_strlen(SEM_ERR));
		close_semaphores(m);
		exit(1);
	}
}

void	init(t_main *m, int argc, char **argv)
{
	m->philo_count = get_number(argv[1]);
	m->time_to_die = get_number(argv[2]);
	m->time_to_eat = get_number(argv[3]);
	m->time_to_sleep = get_number(argv[4]);
	if (argc == 6)
		m->times_to_eat = get_number(argv[5]);
	else
		m->times_to_eat = 0;
	m->forks = NULL;
	m->output = NULL;
	m->finished = NULL;
	m->dead = NULL;
	m->eat = NULL;
	open_semaphores(m);
	m->start_time = get_time();
	if (m->start_time == 0)
	{
		write(2, GET_TIME_ERR, ft_strlen(GET_TIME_ERR));
		exit(1);
	}
}
