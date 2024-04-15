/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:46:05 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 16:21:26 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output_msg(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->output_lock);
	time = get_time() - philo->start_time;
	if (no_deaths(philo))
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->output_lock);
}

int	no_deaths(t_main *m)
{
	pthread_mutex_lock(&m->dead_lock);
	if (m->dead_philo == true)
	{
		pthread_mutex_unlock(&m->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&m->dead_lock);
	return (1);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	output_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	output_msg(philo, "has taken a fork");
	philo->eating = true;
	output_msg(philo, "is eating");
	pthread_mutex_lock(philo->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->time_lock);
	usleep(philo->time_to_eat);
	philo->times_eaten++;
	philo->eating = false;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	routine(void *ptr)
{
	t_main	*m;

	m = (t_main *)ptr;
	if (m->philo->id % 2 == 0)
		usleep(10000);
	while (no_deaths(m))
	{
		philo_eat(philo);
		output_msg(philo, "is sleeping");
		usleep(philo->time_to_sleep);
		output_msg(philo, "is thinking");
	}
	return (ptr);
}
