/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:20:26 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/12 18:03:13 by ade-la-c         ###   ########.fr       */
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
		data->ph[i].times_eated = 0;
		if (pthread_mutex_init(&(data->forks[i]), NULL) == -1)
			return (-1);
	}
	i = -1;
	while (++i < data->nb_of_philo)
		if (data->ph[i].fork1_id == data->ph[i].fork2_id)
			return (-1);
	return (0);
}

static int	init_t_data(t_data *data, int args, char **av)
{
	int	i;

	i = -1;
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->times_must_eat = -1;
	if (args == 5)
		data->times_must_eat = ft_atoi(av[5]);
	data->start_utime = get_utime(0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->forks || init_t_philo(data) == -1)
		return (-1);
	data->all_alive = 1;
	data->start = 0;
	return (0);
}

static void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	free(&(data->forks[i]));
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (printf("Error : wrong number of arguments\n"));
	else if (numeric(av) == -1)
		return (printf("Error : arguments must be only positive integers\n"));
	if (init_t_data(data, ac - 1, av) == -1)
		printf("t_data exit\n");
	if (threading(data) == -1)
		printf("pthread exit\n");
	ft_free(data);
	return (0);
}

//4 410 200 200
