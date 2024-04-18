/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/18 11:59:19 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	m;

	if (invalid_args(argc, argv))
		return (1);
	if (init(&m, argc, argv) != 0)
		return (1);
	if (threads(&m) != 0)
		return (1);
	return (0);
}
