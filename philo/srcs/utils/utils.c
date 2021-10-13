/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:53:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/13 19:37:48 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	print(t_data *data, t_philo *ph, char *action)
{
	if ((data->times_must_eat <= ph->times_eaten && data->times_must_eat != -1)
		|| data->all_alive == 0)
	{
		pthread_mutex_unlock(&(data->print_mutex));
		return ;
	}
	printf("%lu %d %s", get_utime(data->start_utime), ph->ph_id, action);
}

int	ft_usleep(long utime)
{
	long	n;

	n = get_utime(0);
	while (get_utime(0) - n < utime)
	{
		usleep(500);
	}
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
