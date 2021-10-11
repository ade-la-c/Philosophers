//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 03:39:44 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/08 09:01:31 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	does_he_die(t_data *data, t_philo *ph)
{
	if (get_utime(data->start_utime) - ph->last_eat
		> get_utime(data->start_utime) - data->time_to_die)
	{
		ph->is_alive = 0;
		data->all_alive = 0;
		print(data, get_utime(data->start_utime), ph->ph_id, "died\n");
		return (1);
	}
	return (0);
}

int	thinks(t_data *data, t_philo *ph)
{
	print(data, get_utime(data->start_utime), ph->ph_id, "is thinking \n");
	return (0);
}

int	eats_and_sleeps(t_data *data, t_philo *ph)
{
	if (data->forks[ph->fork1_id] == 0 && data->forks[ph->fork2_id] == 0)
	{
		pthread_mutex_lock(&(ph->mutex));
		data->forks[ph->fork1_id] = 1;
		data->forks[ph->fork2_id] = 1;
		ph->last_eat = get_utime(data->start_utime);
		pthread_mutex_lock(&(data->print_mutex));
		print(data, get_utime(data->start_utime), ph->ph_id, "has taken a fork\n");
		print(data, get_utime(data->start_utime), ph->ph_id, "has taken a fork\n");
		print(data, get_utime(data->start_utime), ph->ph_id, "is eating\n");
		pthread_mutex_unlock(&(data->print_mutex));
		if (does_he_die(data, ph))
			return (-1);
		ph->times_eated++;
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&(ph->mutex));
		print(data, get_utime(data->start_utime), ph->ph_id, "is sleeping\n");
		ph->last_sleep = get_utime(data->start_utime);
		usleep(data->time_to_sleep);
		if (does_he_die(data, ph))
			return (-1);
	}
	return (0);
}
