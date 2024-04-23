/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:18:03 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/23 14:49:51 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	output_msg(t_main *m, t_philo *philo, char *msg)
{
	size_t	time;

	sem_wait(m->output);
	time = get_time() - m->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	sem_post(m->output);
}

static void	eat(t_main *m, t_philo *philo)
{
	sem_wait(m->forks);
	output_msg(m, philo, "has taken a fork");
	sem_wait(m->forks);
	output_msg(m, philo, "has taken a fork");
	output_msg(m, philo, "is eating");
	sem_wait(m->eat);
	philo->last_meal = get_time();
	sem_post(m->eat);
	ft_sleep(m->time_to_eat);
	philo->times_eaten++;
	if (m->times_to_eat != 0 && philo->times_eaten == m->times_to_eat)
		sem_post(m->finished);
	sem_post(m->forks);
	sem_post(m->forks);
}

void	*philo_monitor(void *ptr)
{
	size_t	time;
	t_philo	*philo;

	philo = (t_philo *)ptr;
	ft_sleep(10);
	while (1)
	{
		sem_wait(philo->m->eat);
		time = get_time();
		if (time - philo->last_meal > philo->m->time_to_die)
		{
			sem_wait(philo->m->output);
			printf("%zu %d died\n", time - philo->m->start_time, philo->id);
			sem_post(philo->m->dead);
			break ;
		}
		sem_post(philo->m->eat);
		ft_sleep(1);
	}
	return (NULL);
}

void	philo_process(t_main *m, int id)
{
	t_philo	philo;

	sem_wait(m->dead);
	sem_wait(m->finished);
	philo.id = id + 1;
	philo.last_meal = get_time();
	philo.times_eaten = 0;
	philo.m = m;
	if (pthread_create(&philo.monitor, NULL, &philo_monitor, &philo) != 0)
	{
		sem_wait(m->output);
		write(2, THREAD_CREATE_ERR, ft_strlen(THREAD_CREATE_ERR));
		sem_post(m->dead);
		exit(1);
	}
	while (1)
	{
		eat(m, &philo);
		output_msg(m, &philo, "is sleeping");
		ft_sleep(m->time_to_sleep);
		output_msg(m, &philo, "is thinking");
	}
	exit(0);
}

void	fork_philos(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		m->pid[i] = fork();
		if (m->pid[i] == 0)
			philo_process(m, i);
		else if (m->pid[i] < 0)
		{
			write(2, FORK_ERR, ft_strlen(FORK_ERR));
			exit(1);
		}
		i++;
	}
}
