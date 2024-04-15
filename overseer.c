/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:48:56 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 16:15:32 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_dead_philo(t_main *m)
{
	int	i;
	
	i = 0;
	while (i < m->philo_count)
	{

		i++;
	}
	return (0);
}

void	*overseer(void *ptr)
{
	t_main	*m;

	m = (t_main *)ptr;
	while (1)
	{
		if (find_dead_philo(m) || all_done_eating(m))
			break;
	}
	return (ptr);
}
