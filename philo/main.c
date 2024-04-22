/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/22 20:25:38 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main			m;
	t_philo			philos[PHILO_LIMIT];
	pthread_mutex_t	forks[PHILO_LIMIT];

	m.philos = philos;
	m.forks = forks;
	if (invalid_args(argc, argv))
		return (1);
	if (init(&m, argc, argv) != 0)
		return (1);
	if (threads(&m) != 0)
		return (1);
	return (0);
}
