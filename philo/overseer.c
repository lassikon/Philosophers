/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:56 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/25 11:15:02 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_dead_philo(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		pthread_mutex_lock(&m->philos[i].eat_lock);
		if (get_time() - m->philos[i].last_meal > m->time_to_die)
		{
			pthread_mutex_lock(&m->dead_lock);
			m->dead_philo = TRUE;
			pthread_mutex_unlock(&m->dead_lock);
			pthread_mutex_lock(&m->output_lock);
			printf("%zu %d died\n", get_time() - m->start_time, i + 1);
			pthread_mutex_unlock(&m->output_lock);
			pthread_mutex_unlock(&m->philos[i].eat_lock);
			return (1);
		}
		pthread_mutex_unlock(&m->philos[i].eat_lock);
		i++;
	}
	return (0);
}

static int	all_done_eating(t_main *m)
{
	int	i;
	int	done;

	done = 0;
	i = 0;
	while (i < m->philo_count)
	{
		pthread_mutex_lock(&m->philos[i].eat_lock);
		if (m->times_to_eat > 0 && m->philos[i].times_eaten >= m->times_to_eat)
			done++;
		pthread_mutex_unlock(&m->philos[i].eat_lock);
		i++;
	}
	if (done == m->philo_count)
	{
		pthread_mutex_lock(&m->dead_lock);
		m->dead_philo = TRUE;
		pthread_mutex_unlock(&m->dead_lock);
		return (1);
	}
	return (0);
}

void	*overseer(void *ptr)
{
	t_main	*m;

	ft_sleep(10);
	m = (t_main *)ptr;
	while (1)
	{
		if (find_dead_philo(m) || all_done_eating(m))
			break ;
	}
	return (ptr);
}
