/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:43:53 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/24 11:57:37 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_semaphores(t_main *m)
{
	if (m->forks)
		sem_close(m->forks);
	if (m->output)
		sem_close(m->output);
	if (m->finished)
		sem_close(m->finished);
	if (m->dead)
		sem_close(m->dead);
	if (m->eat)
		sem_close(m->eat);
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("finished");
	sem_unlink("dead");
	sem_unlink("eat");
}

int	main(int argc, char **argv)
{
	t_main	m;

	if (invalid_args(argc, argv))
		return (1);
	init(&m, argc, argv);
	fork_philos(&m);
	ft_sleep(10);
	fork_monitors(&m);
	wait_monitors(&m);
	close_semaphores(&m);
	return (0);
}
