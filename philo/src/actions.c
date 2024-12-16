/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:54:39 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/16 11:56:43 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_satiated(t_data *data, int id)
{
	int	i;

	if (data->eat_amount == -1)
		return ;
	pthread_mutex_lock(&data->satiated_mutex);
	data->satiated[id - 1]++;
	i = 0;
	while (i < data->amount)
	{
		if (data->satiated[i] < data->eat_amount)
		{
			pthread_mutex_unlock(&data->satiated_mutex);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->satiated_mutex);
	pthread_mutex_lock(&data->stopped_mutex);
	data->stopped = 1;
	pthread_mutex_unlock(&data->stopped_mutex);
}

void	try_eating(t_data *data, int id, int *forks, long *last_eat)
{
	if (*forks != 2)
		return ;
	printf("%ld %d is eating\n", get_time(), id);
	smart_sleep(data, data->eat);
	check_satiated(data, id);
	if (is_stopped(data))
		return ;
	*forks = 0;
	*last_eat = get_time();
	printf("%ld %d is sleeping\n", get_time(), id);
	pthread_mutex_lock(&data->forks_mutex);
	*get_fork(data, id) = 0;
	*get_fork(data, id + 1) = 0;
	pthread_mutex_unlock(&data->forks_mutex);
	smart_sleep(data, data->sleep);
	if (!is_stopped(data))
		thinking(data, id, *last_eat);
}

void	thinking(t_data *data, int id, long last_eat)
{
	long	remain;

	remain = data->die - (get_time() - last_eat);
	printf("%ld %d is thinking\n", get_time(), id);
	smart_sleep(data, 0 / 10);
}
