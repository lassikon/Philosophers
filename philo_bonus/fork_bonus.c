/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:18:03 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/18 15:48:40 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_death(t_main *m, t_philo *philo)
{
	if (get_time() - philo->last_meal > m->time_to_die)
	{
		sem_wait(m->output);
		printf("%zu %d died\n", get_time() - m->start_time, philo->id);
		sem_post(m->finished);
		exit(1);
	}
}

void	output_msg(t_main *m, t_philo *philo, char *msg)
{
	size_t	time;

	sem_wait(m->output);
	time = get_time() - m->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	sem_post(m->output);
}

void	eat(t_main *m, t_philo *philo)
{
	sem_wait(m->forks);
	check_death(m, philo);
	output_msg(m, philo, "has taken a fork");
	sem_wait(m->forks);
	check_death(m, philo);
	output_msg(m, philo, "has taken a fork");
	output_msg(m, philo, "is eating");
	philo->last_meal = get_time();
	philo->times_eaten++;
	ft_sleep(m->time_to_eat);
	sem_post(m->forks);
	sem_post(m->forks);
}

void	child(t_main *m, int id)
{
	t_philo	philo;

	sem_wait(m->finished);
	philo.id = id + 1;
	philo.last_meal = get_time();
	philo.times_eaten = 0;
	while (1)
	{
		eat(m, &philo);
		output_msg(m, &philo, "is sleeping");
		ft_sleep(m->time_to_sleep);
		check_death(m, &philo);
		output_msg(m, &philo, "is thinking");
	}
	exit(0);
}

void	forks(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		m->pid[i] = fork();
		if (m->pid[i] == 0)
			child(m, i);
		else if (m->pid[i] < 0)
		{
			write(2, FORK_ERR, ft_strlen(FORK_ERR));
			exit(1);
		}
		i++;
	}
}
