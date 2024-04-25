/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:43:10 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/25 12:25:12 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philos(t_main *m, int i)
{
	while (i >= 0)
	{
		kill(m->pid[i], SIGTERM);
		waitpid(m->pid[i], NULL, 0);
		i--;
	}
}

static void	death_monitor(t_main *m)
{
	sem_wait(m->dead);
	kill_philos(m, m->philo_count - 1);
	exit(1);
}

static void	eat_monitor(t_main *m)
{
	int	eaten;

	eaten = 0;
	while (eaten < m->philo_count)
	{
		sem_wait(m->finished);
		eaten++;
	}
	kill_philos(m, m->philo_count - 1);
	exit(0);
}

void	fork_monitors(t_main *m)
{
	m->death_monitor_pid = fork();
	if (m->death_monitor_pid == -1)
	{
		kill_philos(m, m->philo_count - 1);
		close_semaphores(m);
		write(2, FORK_ERR, ft_strlen(FORK_ERR));
		exit(1);
	}
	if (m->death_monitor_pid == 0)
		death_monitor(m);
	m->eat_monitor_pid = fork();
	if (m->eat_monitor_pid == -1)
	{
		kill_philos(m, m->philo_count - 1);
		kill(m->death_monitor_pid, SIGTERM);
		waitpid(m->death_monitor_pid, NULL, 0);
		close_semaphores(m);
		write(2, FORK_ERR, ft_strlen(FORK_ERR));
		exit(1);
	}
	if (m->eat_monitor_pid == 0)
		eat_monitor(m);
}

void	wait_monitors(t_main *m)
{
	int	finished_pid;

	while (1)
	{
		finished_pid = waitpid(m->eat_monitor_pid, NULL, WNOHANG);
		if (finished_pid == m->eat_monitor_pid)
		{
			kill(m->death_monitor_pid, SIGTERM);
			waitpid(m->death_monitor_pid, NULL, 0);
			break ;
		}
		finished_pid = waitpid(m->death_monitor_pid, NULL, WNOHANG);
		if (finished_pid == m->death_monitor_pid)
		{
			kill(m->eat_monitor_pid, SIGTERM);
			waitpid(m->eat_monitor_pid, NULL, 0);
			break ;
		}
	}
}
