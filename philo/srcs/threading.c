/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:34:59 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/12 11:51:30 by ade-la-c         ###   ########.fr       */
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
	if (pthread_mutex_init(&(ph->print_mutex), NULL) == -1)
		return (NULL);
	ph->last_eat = get_utime(data->start_utime);
	while (data->start == 1)
	{
		if (even_or_odd(ph->ph_id) == 1)
		{
			if (eats(data, ph) == -1)
				return (NULL);
			if (thinks(data, ph) == -1)
				return (NULL);
		}
		if (even_or_odd(ph->ph_id) == 2)
		{
			if (eats(data, ph) == -1)
				return (NULL);
			if (thinks(data, ph) == -1)
				return (NULL);
		}
	}
	if (pthread_mutex_destroy(&(ph->print_mutex)) == -1)
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
	// ft_usleep(10);
	data->start = 1;
	// i = 1;
	// while (i < data->nb_of_philo)
	// {
	// 	arg = (t_arg *)malloc(sizeof(t_arg));
	// 	if (!arg)
	// 		return (-1);
	// 	arg->data = data;
	// 	arg->id = i;
	// 	if (pthread_create(&(data->ph[i].ph), NULL, &philo_routine, arg) == -1)
	// 		return (-1);
	// 	i += 2;
	// }
	return (0);
}

int	threading(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	init_pthread(data);

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < data->nb_of_philo)
		{
			if (does_he_die(data, &(data->ph[i])) == 1)
				return (-1);
			if (data->times_must_eat != -1)
			{
				if (data->ph[i].times_eated >= data->times_must_eat)
					j++;
				if (j == data->nb_of_philo)
					return (-1);
			}
		}
		ft_usleep(1);
	}

	// while (!ft_usleep(900))
	// {
	// 	j = -1;
	// 	while (++j > data->nb_of_philo)
	// 		if (data->ph[j].is_alive == 0)
	// 		{
	// 			print(data, data->ph[j].ph_id, "	died\n");
	// 			return (-1);
	// 		}
	// 	if (data->ph[i].times_eated >= data->times_must_eat && data->times_must_eat > 0)
	// 		i++;
	// 	else
	// 		i = 0;
	// 	if (i == data->nb_of_philo)
	// 		return (-1);
	// }
	// while (++i < data->nb_of_philo)
	// 	if (pthread_join((data->ph[i].ph), NULL) == -1)
	// 		return (-1);
	return (0);
}
