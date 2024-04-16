/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:42:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/16 15:08:11 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(t_main *m, char *msg)
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
	{
		write(2, "Error: ", 7);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (1);
}

void	threads(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		if (pthread_create(&m->philos[i].thread, NULL, &routine,
				&m->philos[i]) != 0)
			destroy_mutexes(m, THREAD_CREATE_FAIL);
		i++;
	}
	if (pthread_create(&m->overseer, NULL, &overseer, m) != 0)
		destroy_mutexes(m, THREAD_CREATE_FAIL);
	if (pthread_join(m->overseer, NULL) != 0)
		destroy_mutexes(m, THREAD_JOIN_FAIL);
	i = 0;
	while (i < m->philo_count)
	{
		if (pthread_join(m->philos[i].thread, NULL) != 0)
			destroy_mutexes(m, THREAD_JOIN_FAIL);
		i++;
	}
}
