/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:53:14 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/09 12:55:41 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

// marche pas D:

// void	print(t_data *data, long long utime, int philo, char *action)
// {
// 	int		i;
// 	int		j;
// 	char *str;

// 	i = -1;
// 	j = 0;
// 	// printf(" string : %s\n", data->print_buf);
// 	str = ft_itoa(utime);
// 	i = ft_strlen(data->print_buf) + 1;
// 	data->print_buf[i++] = ' ';
// 	ft_itoa(philo);
// 	i = ft_strlen(data->print_buf) + 1;
// 	while (action[j])
// 		data->print_buf[i++] = action[j++];
// 	// write(1, data->print_buf, ft_strlen(data->print_buf));
// }

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
	return (utime);		// start_utime = 0 to get timeofday
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
