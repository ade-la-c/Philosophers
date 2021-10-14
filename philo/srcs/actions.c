/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:02:51 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/14 14:26:15 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	does_he_die(t_data *data, t_philo *ph)
{
	if (stop_simulation(data, ph))
		return (0);
	if (get_utime(data->start_utime) - ph->last_eat >= data->time_to_die)
	{
		ph->is_alive = 0;
		pthread_mutex_lock(&(data->print_mutex));
		print(data, ph, "died\n");
		data->all_alive = 0;
		return (1);
	}
	return (0);
}

int	thinks(t_data *data, t_philo *ph)
{
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph, "is thinking\n");
	pthread_mutex_unlock(&(data->print_mutex));
	return (0);
}

int	sleeps(t_data *data, t_philo *ph)
{
	if (stop_simulation(data, ph))
		return (-1);
	ph->times_eaten++;
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph, "is sleeping\n");
	pthread_mutex_unlock(&(data->print_mutex));
	ft_usleep(data->time_to_sleep);
	return (0);
}

int	eats(t_data *data, t_philo *ph)
{
	if (stop_simulation(data, ph))
		return (-1);
	pthread_mutex_lock(&(data->forks[ph->fork1_id]));
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph, "has taken a fork\n");
	pthread_mutex_unlock(&(data->print_mutex));
	pthread_mutex_lock(&(data->forks[ph->fork2_id]));
	pthread_mutex_lock(&(data->print_mutex));
	print(data, ph, "has taken a fork\n");
	print(data, ph, "is eating\n");
	pthread_mutex_unlock(&(data->print_mutex));
	ph->last_eat = get_utime(data->start_utime);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&(data->forks[ph->fork1_id]));
	pthread_mutex_unlock(&(data->forks[ph->fork2_id]));
	if (sleeps(data, ph) == -1)
		return (-1);
	return (0);
}
