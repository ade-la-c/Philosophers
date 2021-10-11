/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 12:29:51 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/11 11:08:53 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// int	nbr_len(t_data *data, long num)
// {
// 	int	i;

// 	i = 1;
// 	while (num >= 10)
// 	{
// 		num /= 10;
// 		i++;
// 	}
// 	return (i);
// }

static void	nbr_to_buf(t_data *data, int nb)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		nbr_to_buf(data, nb / 10);
		nbr_to_buf(data, nb % 10);
	}
	else
		data->print_buf[(data->buf_len)++] = nb + '0';
}

void	print(t_data *data, long utime, int philo, char *action)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->print_mutex));
	if (data->all_alive == 0)
		return ;
	data->buf_len = 0;
	nbr_to_buf(data, utime);
	data->print_buf[data->buf_len++] = ' ';
	nbr_to_buf(data, philo);
	data->print_buf[data->buf_len++] = ' ';
	while (action[i])
		data->print_buf[data->buf_len++] = action[i++];
	write(1, data->print_buf, ft_strlen(data->print_buf));
	i = -1;
	while (data->print_buf[++i])
		data->print_buf[i] = 0;
	pthread_mutex_unlock(&(data->print_mutex));
	// printf("~~%s~~\n", data->print_buf);
}
