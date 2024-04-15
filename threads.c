/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:42:07 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 16:18:27 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads(t_main *m)
{
	int	i;

	if (pthread_create(&m->overseer, NULL, &overseer, m) != 0)
		error_exit("THREAD");
	i = 0;
	while (i < m->philo_count)
	{
		if (pthread_create(&m->philos[i].thread, NULL, &routine, m) != 0)
			error_exit("THREAD");
		i++;
	}
	if (pthread_join(m->overseer, NULL) != 0)
		error_exit("THREAD");
	i = 0;
	while (i < m->philo_count)
	{
		if (pthread_join(m->philos[i].thread, NULL) != 0)
			error_exit("THREAD");
		i++;
	}
}
