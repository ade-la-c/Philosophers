/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:53:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/12 11:03:40 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_usleep(long utime)
{
	utime *= 1000;
	usleep(utime - (utime / 4));
	usleep(utime / 8);
	usleep(utime / 8);
	return (0);
}

int	even_or_odd(int i)
{
	if ((i % 2) == 0)
		return (2);
	else
		return (1);
}

long	get_utime(long start_utime)
{
	unsigned long	utime;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	utime = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	utime -= start_utime;
	return (utime);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	return (num);
}
