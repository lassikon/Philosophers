/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:43:53 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/18 15:22:00 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philos(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->philo_count)
	{
		kill(m->pid[i], SIGKILL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_main	m;

	if (invalid_args(argc, argv))
		return (1);
	init(&m, argc, argv);
	forks(&m);
	ft_sleep(10);
	sem_wait(m.finished);
	kill_philos(&m);
	sem_close(m.forks);
	sem_close(m.output);
	sem_close(m.finished);
	return (0);
}
