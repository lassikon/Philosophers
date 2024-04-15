/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:55:49 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/15 12:56:21 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	not_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	invalid_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "Error: Invalid number of arguments\n", 37));
	if (not_digit(argv[1]) || ft_atoi(argv[1]) < 1
		|| ft_atoi(argv[1]) > PHILO_LIMIT)
		return (write(2, "Error: Invalid philosopher count\n", 35));
	if (not_digit(argv[2] || ft_atoi(argv[2] < 1)))
		return (write(2, "Error: Invalid time to die\n", 29));
	if (not_digit(argv[3] || ft_atoi(argv[3] < 1)))
		return (write(2, "Error: Invalid time to eat\n", 29));
	if (not_digit(argv[4] || ft_atoi(argv[4] < 1)))
		return (write(2, "Error: Invalid time to sleep\n", 31));
	if (argc == 6)
		if (not_digit(argv[5] || ft_atoi(argv[5] < 0)))
			return (write(2, "Error: Invalid number of times to eat\n", 41));
	return (0);
}