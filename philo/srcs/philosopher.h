/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:20:57 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/12 11:10:11 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <errno.h>

typedef struct s_philo
{
	pthread_t		ph;
	int				ph_id;
	int				fork1_id;
	int				fork2_id;
	long 			last_eat;			// last time philo ate
	int				times_eated;
	long 			last_sleep;			// last time philo slept
	int				is_alive;
	pthread_mutex_t	print_mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long 			start_utime;		// time of start of simulation (usec)
	pthread_mutex_t	*forks;
	t_philo			*ph;
	char			*print_buf;
	int				buf_len;
	pthread_t		death_thread;
	int				all_alive;
	pthread_mutex_t	print_mutex;
	int				start;
}	t_data;

typedef struct s_arg
{
	t_data			*data;
	int				id;
}	t_arg;

//=============UTILS=============//

int					ft_usleep(long utime);
void				*ft_calloc(size_t count, size_t size);
void				print(t_data *data, int philo, char *action);
int					even_or_odd(int i);
long 				get_utime(long utime_of_start);
int					ft_atoi(const char *str);
int					ft_strlen(char *str);
char				*ft_itoa(int n);


//============THREADS============//

int					threading(t_data *data);
void				*philo_routine(void *ptr);
// int					even_routine(t_data *data, t_philo *ph);
// int					odd_routine(t_data *data, t_philo *ph);

//============ACTIONS============//

int					thinks(t_data *data, t_philo *ph);
int					eats(t_data *data, t_philo *ph);
int					sleeps(t_data *data, t_philo *ph);
int					does_he_die(t_data *data, t_philo *ph);

#endif
