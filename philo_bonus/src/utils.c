/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:06:54 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/20 15:35:23 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	print(t_data *data, char *action)
{
	int	ignore;

	(void) ignore;
	sem_wait(data->writing);
	if (!data->philo.stopped)
	{
		ft_putnbr(get_time());
		ignore = write(1, " ", 1);
		ft_putnbr(data->philo.id + 1);
		ignore = write(1, " ", 1);
		ignore = write(1, action, ft_strlen(action));
		ignore = write(1, "\n", 1);
	}
	sem_post(data->writing);
}

void	philo_sleep(t_data *data, unsigned int ms)
{
	unsigned int	i;

	i = 0;
	while (!data->philo.stopped && i + 100 <= ms)
	{
		usleep(100 * 1e3);
		i += 100;
	}
	if (!data->philo.stopped && i < ms)
		usleep((ms - i) * 1e3);
}

void	stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		sem_post(data->stopped);
		i++;
	}
	usleep(500);
	sem_post(data->writing);
}
