/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:46:05 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/16 15:27:07 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	no_deaths(t_main *m)
{
	pthread_mutex_lock(&m->dead_lock);
	if (m->dead_philo == TRUE)
	{
		pthread_mutex_unlock(&m->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&m->dead_lock);
	return (1);
}

void	output_msg(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->m->output_lock);
	time = get_time() - philo->m->start_time;
	if (no_deaths(philo->m))
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->m->output_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	output_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	output_msg(philo, "has taken a fork");
	output_msg(philo, "is eating");
	pthread_mutex_lock(&philo->eat_lock);
	philo->eating = TRUE;
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_lock(&philo->m->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m->time_lock);
	usleep(philo->m->time_to_eat * 1000);
	philo->eating = FALSE;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	while (no_deaths(philo->m))
	{
		philo_eat(philo);
		output_msg(philo, "is sleeping");
		usleep(philo->m->time_to_sleep * 1000);
		output_msg(philo, "is thinking");
	}
	return (ptr);
}
