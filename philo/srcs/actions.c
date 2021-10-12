/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:02:51 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/12 11:49:07 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	does_he_die(t_data *data, t_philo *ph)
{
	if (ph->last_eat > data->time_to_die)
	{
		ph->is_alive = 0;
		pthread_mutex_lock(&(data->print_mutex));
		print(data, ph->ph_id, "died\n");
		pthread_mutex_unlock(&(data->print_mutex));
		data->all_alive = 0;
		return (1);
	}
	return (0);
}

int	thinks(t_data *data, t_philo *ph)
{
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph->ph_id, "is thinking\n");
	pthread_mutex_unlock(&(data->print_mutex));
	return (0);
}

int	sleeps(t_data *data, t_philo *ph)
{
	if (data->all_alive == 0)
		return (-1);
	ph->times_eated++;
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph->ph_id, "is sleeping\n");
	pthread_mutex_unlock(&(data->print_mutex));
	ph->last_sleep = get_utime(data->start_utime);
	ft_usleep(data->time_to_sleep);
	return (0);
}

int	eats(t_data *data, t_philo *ph)
{
	if (data->all_alive == 0)
		return (-1);
	pthread_mutex_lock(&(data->forks[ph->fork1_id]));
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph->ph_id, "has taken a fork (1)\n");
	pthread_mutex_unlock(&(data->print_mutex));
	pthread_mutex_lock(&(data->forks[ph->fork2_id]));
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph->ph_id, "has taken a fork (2)\n");
	print(data, ph->ph_id, "is eating\n");
	ph->last_eat = get_utime(data->start_utime);
	ft_usleep(data->time_to_eat);
	if (sleeps(data, ph) == -1)
		return (-1);
	pthread_mutex_unlock(&(data->print_mutex));
	pthread_mutex_unlock(&(data->forks[ph->fork1_id]));
	pthread_mutex_unlock(&(data->forks[ph->fork2_id]));
	return (0);
}

	// pthread_mutex_lock(&(mutex));
	// pthread_mutex_unlock(&(mutex));
