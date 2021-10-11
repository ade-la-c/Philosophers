/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:34:59 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/11 10:55:08 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*death_routine(void *ptr)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)ptr;
	while (1)
	{
		if (data->all_alive == 0)
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_data	*data;
	t_philo	*ph;

	data = ((t_arg *)ptr)->data;
	ph = &(((t_arg *)ptr)->data->ph[((t_arg *)ptr)->id]);
	free(ptr);
	if (pthread_mutex_init(&(ph->mutex), NULL) == -1)
		return (NULL);
	while (data->all_alive == 1)
	{
		if (even_or_odd(data->nb_of_philo) == 2)
		{
			if (even_or_odd(ph->ph_id) == 1)
			{
				if (eats_and_sleeps(data, ph) == -1)
					return (NULL);
				thinks(data, ph);
				usleep(100);
			}
			else if (even_or_odd(ph->ph_id) == 2)
			{
				thinks(data, ph);
				usleep(100);
				if (eats_and_sleeps(data, ph))
					return (NULL);
			}
		}
	}
	if (pthread_mutex_destroy(&(ph->mutex)) == -1)
		return (NULL);
	return (NULL);
}

int	init_pthread(t_data *data)
{
	int		i;
	t_arg	*arg;
	
	i = -1;
	if (pthread_create(&(data->death_thread), NULL, &death_routine, data) == -1)
		return (-1);
	while (++i < data->nb_of_philo)
	{
		arg = (t_arg *)malloc(sizeof(t_arg));
		if (!arg)
			return (-1);
		arg->data = data;
		arg->id = i;
		if (pthread_create(&(data->ph[i].ph), NULL, &philo_routine, arg) == -1)
			return (-1);
	}
	while (1)
	{
		if (data->all_alive == 0)
			exit(0);
	}
	i = -1;
	if (data->all_alive == 0)
		if (pthread_join(data->death_thread, NULL) == -1)
			return (-1);
	while (++i < data->nb_of_philo)
		if (pthread_join((data->ph[i].ph), NULL) == -1)
			return (-1);
	return (0);
}
