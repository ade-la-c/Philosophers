/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:20:26 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/15 15:47:33 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	numeric(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (-1);
		if (!ft_strlen(av[i]))
			return (-1);
		j = 0;
		while (av[i][j])
			j++;
		if (j > 10)
			return (-1);
		if (ft_atoi(av[i]) == 0)
			return (-1);
	}
	return (0);
}

static int	init_t_philo(t_data *data)
{
	int	i;

	i = -1;
	data->ph = ft_calloc(data->nb_of_philo, sizeof(t_philo));
	if (!data->ph)
		return (-1);
	while (++i < data->nb_of_philo)
	{
		data->ph[i].ph_id = i + 1;
		data->ph[i].fork1_id = i;
		data->ph[i].fork2_id = i + 1;
		if (data->ph[i].ph_id == data->nb_of_philo)
			data->ph[i].fork2_id = 0;
		data->ph[i].is_alive = 1;
		data->ph[i].times_eaten = 0;
		if (pthread_mutex_init(&(data->forks[i]), NULL) == -1)
			return (-1);
	}
	i = -1;
	while (++i < data->nb_of_philo && data->nb_of_philo != 1)
		if (data->ph[i].fork1_id == data->ph[i].fork2_id)
			return (-1);
	return (0);
}

static int	init_t_data(t_data *data, int args, char **av)
{
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->times_must_eat = -1;
	if (args == 5)
		data->times_must_eat = ft_atoi(av[5]) + 1;
	data->start_utime = get_utime(0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->forks)
		return (-1);
	if (init_t_philo(data) == -1)
		return (-1);
	data->all_alive = 1;
	data->start = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("Error : wrong number of arguments\n"));
	else if (numeric(av) == -1)
		return (printf("Error : arguments must be only positive integers\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (-1);
	if (init_t_data(data, ac - 1, av) == -1)
		return (0);
	if (threading(data) == -1)
		return (0);
	free(data);
	return (0);
}
