/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:34:59 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/17 17:00:45 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routine(void *ptr)
{
	t_data	*data;
	t_philo	*ph;

	data = ((t_arg *)ptr)->data;
	ph = &(((t_arg *)ptr)->data->ph[((t_arg *)ptr)->id]);
	free(ptr);
	if (pthread_mutex_init(&(data->print_mutex), NULL) == -1)
		return (NULL);
	while (data->start != 1)
		usleep(600);
	ph->last_eat = get_utime(data->start_utime);
	if (even_or_odd(ph->ph_id) == 1)
		ft_usleep(data->time_to_eat / 2);
	while (1)
	{
		if (eats(data, ph) == -1)
			break ;
		if (thinks(data, ph) == -1)
			break ;
	}
	pthread_mutex_unlock(&(data->print_mutex));
	if (pthread_mutex_destroy(&(data->print_mutex)) == -1
		|| pthread_mutex_destroy(&(data->forks[ph->fork1_id])) == -1)
		return (NULL);
	return (NULL);
}

int	init_pthread(t_data *data)
{
	int		i;
	t_arg	*arg;

	i = 0;
	while (i < data->nb_of_philo)
	{
		arg = (t_arg *)malloc(sizeof(t_arg));
		if (!arg)
			return (-1);
		arg->data = data;
		arg->id = i;
		if (pthread_create(&(data->ph[i].ph), NULL, &philo_routine, arg) == -1)
			return (-1);
		i++;
	}
	data->start = 1;
	return (0);
}

int	threading(t_data *data)
{
	int		i;

	i = -1;
	if (init_pthread(data) == -1)
		return (-1);
	while (1)
	{
		i = -1;
		while (++i < data->nb_of_philo)
		{
			if (does_he_die(data, &(data->ph[i])) == 1)
				return (0);
			if (data->times_must_eat != -1)
				if (stop_simulation(data, &(data->ph[i])))
					return (0);
		}
		ft_usleep(1);
	}
	return (0);
}
