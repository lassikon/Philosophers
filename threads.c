/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:42:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/17 16:45:01 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexes(t_main *m, char *msg)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		pthread_mutex_destroy(&m->forks[i]);
		pthread_mutex_destroy(&m->philos[i].eat_lock);
		i++;
	}
	pthread_mutex_destroy(&m->dead_lock);
	pthread_mutex_destroy(&m->output_lock);
	pthread_mutex_destroy(&m->time_lock);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (1);
}

static int	thread_creation_fail(t_main *m)
{
	write(2, THREAD_CREATE_ERR, ft_strlen(THREAD_CREATE_ERR));
	pthread_mutex_lock(&m->dead_lock);
	m->dead_philo = TRUE;
	pthread_mutex_unlock(&m->dead_lock);
	if (pthread_join(m->overseer, NULL) != 0)
		return (destroy_mutexes(m, THREAD_JOIN_ERR));
	while (m->threads_created > 0)
	{
		m->threads_created--;
		if (pthread_join(m->philos[m->threads_created].thread, NULL) != 0)
			return (destroy_mutexes(m, THREAD_JOIN_ERR));
	}
	return (destroy_mutexes(m, NULL));
}

int	threads(t_main *m)
{
	if (pthread_create(&m->overseer, NULL, &overseer, m) != 0)
		return (destroy_mutexes(m, THREAD_CREATE_ERR));
	while (m->threads_created < m->philo_count)
	{
		if (pthread_create(&m->philos[m->threads_created].thread, NULL,
				&routine, &m->philos[m->threads_created]) != 0)
			return (thread_creation_fail(m));
		m->threads_created++;
	}
	if (pthread_join(m->overseer, NULL) != 0)
		return (destroy_mutexes(m, THREAD_JOIN_ERR));
	while (m->threads_created > 0)
	{
		m->threads_created--;
		if (pthread_join(m->philos[m->threads_created].thread, NULL) != 0)
			return (destroy_mutexes(m, THREAD_JOIN_ERR));
	}
	destroy_mutexes(m, NULL);
	return (0);
}
