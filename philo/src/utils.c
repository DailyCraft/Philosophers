/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:25:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 17:13:36 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

int	is_stopped(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->data->stopped_mutex);
	stopped = philo->data->stopped;
	pthread_mutex_unlock(&philo->data->stopped_mutex);
	return (stopped);
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!is_stopped(philo))
		printf("%ld %d %s\n", get_time(), philo->id + 1, action);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	philo_sleep(t_philo *philo, unsigned int ms)
{
	unsigned int	i;

	i = 0;
	while (!is_stopped(philo) && i + 100 <= ms)
	{
		usleep(100 * 1e3);
		i += 100;
	}
	if (!is_stopped(philo) && i < ms)
		usleep((ms - i) * 1e3);
}
