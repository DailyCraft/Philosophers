/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:25:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/11 11:44:45 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	secure_atoi(char *str, int *err)
{
	unsigned int	result;
	int				neg;

	result = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result * 10 + *str - '0' > (unsigned) 2147483647 + (neg == -1))
			return (*err = 1, 0);
		result = result * 10 + *str - '0';
		str++;
	}
	if (*str)
		return (*err = 1, 0);
	return (result * neg);
}

long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

int	get_fork(t_data *data, int index)
{
	int	id;

	//pthread_mutex_lock(&data->forks_mutex);
	id = data->forks_owner[(index - 1) % data->amount];
	//pthread_mutex_unlock(&data->forks_mutex);
	return (id);
}

void	set_fork(t_data *data, int index, int id)
{
	//pthread_mutex_lock(&data->forks_mutex);
	data->forks_owner[(index - 1) % data->amount] = id;
	//pthread_mutex_unlock(&data->forks_mutex);
}

int	is_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stopped_mutex);
	stopped = data->stopped;
	pthread_mutex_unlock(&data->stopped_mutex);
	return (stopped);
}
