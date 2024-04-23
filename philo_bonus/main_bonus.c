/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:43:53 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/23 14:18:56 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_close(m.forks);
	sem_close(m.output);
	sem_close(m.finished);
	sem_close(m.dead);
	sem_close(m.eat);
	return (0);
}
