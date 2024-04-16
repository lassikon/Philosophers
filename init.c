/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:04:14 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/16 15:35:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		m->philos[i].id = i + 1;
		// printf("Philosopher %d created\n", m->philos[i].id);
		m->philos[i].eating = FALSE;
		m->philos[i].left_fork = &m->forks[i];
		if (i == m->philo_count - 1)
			m->philos[i].right_fork = &m->forks[0];
		else
			m->philos[i].right_fork = &m->forks[i + 1];
		m->philos[i].times_eaten = 0;
		m->philos[i].m = m;
		pthread_mutex_init(&m->philos[i].eat_lock, NULL);
		m->philos[i].last_meal = get_time();
		i++;
	}
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

void	init(t_main *m, int argc, char **argv)
{
	t_philo			philos[PHILO_LIMIT];
	pthread_mutex_t forks[PHILO_LIMIT];

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
	m->error = FALSE;
	m->dead_philo = FALSE;
	m->start_time = get_time();
	init_philos(m);
}
