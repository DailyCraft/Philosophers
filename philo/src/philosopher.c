/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:50:40 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/11 11:43:45 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	try_take_forks(t_data *data, int id, int *forks)
{
	pthread_mutex_lock(&data->forks_mutex);
	if (get_fork(data, id) == 0)
	{
		(*forks)++;
		set_fork(data, id, id);
		printf("%ld %d has taken a fork\n", get_time(), id);
	}
	if (get_fork(data, id + 1) == 0)
	{
		(*forks)++;
		set_fork(data, id + 1, id);
		printf("%ld %d has taken a fork\n", get_time(), id);
	}
	pthread_mutex_unlock(&data->forks_mutex);
}

static void	try_eating(t_data *data, int id, int *forks, long *last_eat)
{
	if (*forks != 2)
		return ;
	printf("%ld %d is eating\n", get_time(), id);
	usleep(data->eat * 1e3);
	if (is_stopped(data))
		return ;
	*forks = 0;
	*last_eat = get_time();
	pthread_mutex_lock(&data->forks_mutex);
	set_fork(data, id, 0);
	set_fork(data, id + 1, 0);
	pthread_mutex_unlock(&data->forks_mutex);
	printf("%ld %d is sleeping\n", get_time(), id);
	usleep(data->sleep * 1e3);
	if (!is_stopped(data))
		printf("%ld %d is thinking\n", get_time(), id);
}

static void	can_survive(t_data *data, int id, long last_eat)
{
	if (get_time() - last_eat < data->die)
		return ;
	pthread_mutex_lock(&data->stopped_mutex);
	if (!data->stopped)
		printf("%ld %d died\n", get_time(), id);
	data->stopped = 1;
	pthread_mutex_unlock(&data->stopped_mutex);
}

void	*action(t_data *data)
{
	static int	thread_id_counter = 1;
	int			thread_id;
	int			forks;
	long		last_eat;

	thread_id = thread_id_counter++;
	forks = 0;
	last_eat = get_time();
	while (!is_stopped(data))
	{
		try_take_forks(data, thread_id, &forks);
		try_eating(data, thread_id, &forks, &last_eat);
		if (!is_stopped(data))
			can_survive(data, thread_id, last_eat);
	}
	return (NULL);
}
