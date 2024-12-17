/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:25:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/17 16:59:55 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	smart_sleep(t_data *data, unsigned int ms)
{
	unsigned int	i;

	(void) data;
	i = 0;
	while (1 && i + 100 <= ms)
	{
		usleep(100 * 1e3);
		i += 100;
	}
	if (1 && i < ms)
		usleep((ms - i) * 1e3);
}

void	log(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("%ld %d %s\n", get_time(), philo->id + 1, action);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
