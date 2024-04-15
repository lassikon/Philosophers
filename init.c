/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:04:14 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 16:12:49 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		m->philos->id = i + 1;
		m->philos->eating = false;
		m->philos->dead_philo = &m->dead_philo;
		m->philos->dead_lock = &m->dead_lock;
		m->philos->output_lock = &m->output_lock;
		m->philos->time_lock = &m->time_lock;
		m->philos->left_fork = &m->forks[i];
		if (i == m->philo_count - 1)
			m->philos->right_fork = &m->forks[0];
		else
			m->philos->right_fork = &m->forks[i + 1];
		m->philos->times_eaten = 0;
		m->philos->time_to_die = m->time_to_die;
		m->philos->time_to_eat = m->time_to_eat;
		m->philos->time_to_sleep = m->time_to_sleep;
		m->philos->start_time = get_time();
		m->philos->last_meal = get_time();
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
		m->times_to_eat = -1;
	m->forks = forks;
	init_mutexes(m);
	m->philos = philos;
	m->error = false;
	m->dead_philo = false;
	init_philos(m);
}
