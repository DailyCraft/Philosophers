/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:58:41 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/20 15:35:19 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	eat(t_data *data)
{
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
	print(data, "is eating");
	data->philo.last_eat = get_time();
	data->philo.eat_count++;
	philo_sleep(data, data->eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*checker(t_data *data)
{
	int	already_post;

	already_post = 0;
	while (!data->philo.stopped)
	{
		if (get_time() - data->philo.last_eat >= data->die)
		{
			sem_wait(data->writing);
			printf("%ld %d died\n", get_time(), data->philo.id + 1);
			//sem_post(data->writing);
			stop(data);
			return (NULL);
		}
		if (data->eat_amount != -1 && !already_post
			&& data->philo.eat_count >= data->eat_amount)
		{
			sem_post(data->all_ate);
			already_post = 1;
		}
		usleep(100);
	}
	return (NULL);
}

static void	*stopper(t_data *data)
{
	sem_wait(data->stopped);
	data->philo.stopped = 1;
	return (NULL);
}

void	philo(t_data *data)
{
	sem_wait(data->start);
	sem_post(data->start);
	data->philo.last_eat = get_time();
	if (data->philo.id % 2)
		usleep(3e3);
	pthread_create(&data->philo.checker, NULL,
		(void *(*)(void *)) checker, data);
	pthread_create(&data->philo.stopper, NULL,
		(void *(*)(void *)) stopper, data);
	while (!data->philo.stopped)
	{
		eat(data);
		print(data, "is sleeping");
		philo_sleep(data, data->sleep);
		print(data, "is thinking");
	}
	printf("a\n");
	pthread_join(data->philo.checker, NULL);
	printf("b\n");
	pthread_join(data->philo.stopper, NULL);
	printf("c\n");
}
