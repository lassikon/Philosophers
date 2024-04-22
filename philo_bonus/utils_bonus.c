/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:06:30 by lkonttin          #+#    #+#             */
/*   Updated: 2024/04/22 13:39:28 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_number(const char *str)
{
	long	nbr;

	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - '0';
		if (nbr > 2147483647)
			return (-1);
		str++;
	}
	return ((int)nbr);
}

size_t	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		write(2, GET_TIME_ERR, ft_strlen(GET_TIME_ERR));
		return (0);
	}
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_sleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(500);
}
