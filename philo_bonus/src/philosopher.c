/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:58:41 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/29 08:52:56 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	eat(t_data *data)
{
	static int	eat_count = 0;

	sem_wait(data->forks);
	print(data, "has taken a fork");
	if (data->philo.id == (data->philo.id + 1) % data->amount)
	{
		philo_sleep(data, data->die);
		sem_post(data->forks);
		return ;
	}
	sem_wait(data->forks);
	print(data, "has taken a fork");
	sem_wait(data->eat_check);
	print(data, "is eating");
	data->philo.last_eat = get_time();
	sem_post(data->eat_check);
	eat_count++;
	if (data->eat_amount != -1 && eat_count == data->eat_amount)
		sem_post(data->all_ate);
	philo_sleep(data, data->eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*checker(t_data *data)
{
	while (!data->philo.stopped)
	{
		sem_wait(data->eat_check);
		if (get_time() - data->philo.last_eat >= data->die)
		{
			sem_wait(data->writing);
			if (!data->philo.stopped)
				printf("%ld %d died\n", get_time(), data->philo.id + 1);
			if (!data->philo.stopped)
				stop(data);
			else
				sem_post(data->writing);
			return (NULL);
		}
		sem_post(data->eat_check);
		usleep(100);
	}
	return (NULL);
}

static void	*stopper(t_data *data)
{
	sem_wait(data->stopped);
	data->philo.stopped = 1;
	sem_post(data->all_stopped);
	return (NULL);
}

static void	*loop(t_data *data)
{
	while (!data->philo.stopped)
	{
		eat(data);
		print(data, "is sleeping");
		philo_sleep(data, data->sleep);
		print(data, "is thinking");
	}
	return (NULL);
}

void	philo(t_data *data)
{
	sem_wait(data->start);
	sem_post(data->start);
	data->philo.last_eat = get_time();
	if (data->philo.id % 2)
		usleep(3e3);
	pthread_create(&data->philo.loop, NULL,
		(void *(*)(void *)) loop, data);
	pthread_create(&data->philo.stopper, NULL,
		(void *(*)(void *)) stopper, data);
	checker(data);
	pthread_join(data->philo.loop, NULL);
	pthread_join(data->philo.stopper, NULL);
}
