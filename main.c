/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 16:04:12 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time()
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		error_exit("gettimeofday error");
	return (current_time.tv_usec);
}

int	main(int argc, char **argv)
{
	t_main 			m;

	if (invalid_args(argc, argv))
		return (1);
	init(&m, argc, argv);
	threads(&m);
}