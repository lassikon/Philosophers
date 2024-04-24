/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:46:05 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/24 11:13:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	deaths(t_main *m)
{
	pthread_mutex_lock(&m->dead_lock);
	if (m->dead_philo == TRUE)
	{
		pthread_mutex_unlock(&m->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&m->dead_lock);
	return (0);
}

void	output_msg(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->m->output_lock);
	time = get_time() - philo->m->start_time;
	if (deaths(philo->m) == 0)
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->m->output_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	output_msg(philo, "has taken a fork");
	if (philo->left_fork == philo->right_fork)
	{
		ft_sleep(philo->m->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->m->dead_lock);
		philo->m->dead_philo = TRUE;
		pthread_mutex_unlock(&philo->m->dead_lock);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	output_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eat_lock);
	output_msg(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->eat_lock);
	ft_sleep(philo->m->time_to_eat);
	pthread_mutex_lock(&philo->eat_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_sleep(1);
	while (1)
	{
		philo_eat(philo);
		if (deaths(philo->m))
			break ;
		output_msg(philo, "is sleeping");
		if (philo->m->time_to_sleep + philo->m->time_to_eat
			>= philo->m->time_to_die)
			ft_sleep(philo->m->time_to_die - philo->m->time_to_eat);
		else
			ft_sleep(philo->m->time_to_sleep);
		if (deaths(philo->m))
			break ;
		output_msg(philo, "is thinking");
	}
	return (ptr);
}
