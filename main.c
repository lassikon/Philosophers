/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/17 15:52:13 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	m;

	if (argc < 5 || argc > 6)
		return (write(2, ARG_COUNT_ERR, ft_strlen(ARG_COUNT_ERR)));
	if (init(&m, argc, argv) != 0)
		return (1);
	if (threads(&m) != 0)
		return (1);
	return (0);
}
