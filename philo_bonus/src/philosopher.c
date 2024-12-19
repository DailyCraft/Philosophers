/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:58:41 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 23:10:33 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	eat(t_data *data)
{
	sem_wait(data->forks);
	print(data, "has taken a fork");
	if (data->philo.id == (data->philo.id + 1) % data->amount)
	{
		usleep(data->die * 1e3);
		sem_post(data->forks);
		return ;
	}
	sem_wait(data->forks);
	print(data, "has taken a fork");
	print(data, "is eating");
	data->philo.last_eat = get_time();
	data->philo.eat_count++;
	usleep(data->eat * 1e3);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*checker(t_data *data)
{
	while (1)
	{
		if (get_time() - data->philo.last_eat >= data->die)
		{
			print(data, "died");
			sem_wait(data->writing);
			exit(1);
		}
	}
	return (NULL);
}

void	philo(t_data *data)
{
	sem_wait(data->stopped);
	sem_post(data->stopped);
	data->philo.last_eat = get_time();
	if (data->philo.id % 2)
		usleep(3e3);
	pthread_create(&data->philo.checker, NULL,
		(void *(*)(void *)) checker, data);
	while (1)
	{
		eat(data);
		print(data, "is sleeping");
		usleep(data->sleep * 1e3);
		print(data, "is thinking");
	}
	pthread_join(data->philo.checker, NULL);
}
