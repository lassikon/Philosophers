/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:04:14 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/18 12:00:53 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (argc < 5 || argc > 6)
		return (write(2, ARG_COUNT_ERR, ft_strlen(ARG_COUNT_ERR)));
	if (not_digit(argv[1]) || ft_atoi(argv[1]) < 1
		|| ft_atoi(argv[1]) > PHILO_LIMIT)
		return (write(2, PHILO_COUNT_ERR, ft_strlen(PHILO_COUNT_ERR)));
	if (not_digit(argv[2]) || ft_atoi(argv[2]) < 1)
		return (write(2, TIME_TO_DIE_ERR, ft_strlen(TIME_TO_DIE_ERR)));
	if (not_digit(argv[3]) || ft_atoi(argv[3]) < 1)
		return (write(2, TIME_TO_EAT_ERR, ft_strlen(TIME_TO_EAT_ERR)));
	if (not_digit(argv[4]) || ft_atoi(argv[4]) < 1)
		return (write(2, TIME_TO_SLEEP_ERR, ft_strlen(TIME_TO_SLEEP_ERR)));
	if (argc == 6)
		if (not_digit(argv[5]) || ft_atoi(argv[5]) < 0)
			return (write(2, TIMES_TO_EAT_ERR, ft_strlen(TIMES_TO_EAT_ERR)));
	return (0);
}

static int	init_philos(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		m->philos[i].id = i + 1;
		m->philos[i].left_fork = &m->forks[i];
		if (i == m->philo_count - 1)
			m->philos[i].right_fork = &m->forks[0];
		else
			m->philos[i].right_fork = &m->forks[i + 1];
		m->philos[i].times_eaten = 0;
		m->philos[i].m = m;
		pthread_mutex_init(&m->philos[i].eat_lock, NULL);
		m->philos[i].last_meal = get_time();
		if (m->philos[i].last_meal == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	init_mutexes(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		pthread_mutex_init(&m->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&m->dead_lock, NULL);
	pthread_mutex_init(&m->output_lock, NULL);
	pthread_mutex_init(&m->time_lock, NULL);
}

int	init(t_main *m, int argc, char **argv)
{
	t_philo			philos[PHILO_LIMIT];
	pthread_mutex_t	forks[PHILO_LIMIT];

	m->philo_count = ft_atoi(argv[1]);
	m->time_to_die = ft_atoi(argv[2]);
	m->time_to_eat = ft_atoi(argv[3]);
	m->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		m->times_to_eat = ft_atoi(argv[5]);
	else
		m->times_to_eat = 0;
	m->forks = forks;
	init_mutexes(m);
	m->philos = philos;
	m->dead_philo = FALSE;
	m->threads_created = 0;
	m->start_time = get_time();
	if (m->start_time == 0)
		return (1);
	if (init_philos(m) == 1)
		return (1);
	return (0);
}
