/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:07:24 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/16 14:46:36 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return ;
}

size_t	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		error_exit("gettimeofday error");
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	t_main	m;

	if (invalid_args(argc, argv))
		return (1);
	init(&m, argc, argv);
	threads(&m);
	destroy_mutexes(&m, NULL);
	return (0);
}
