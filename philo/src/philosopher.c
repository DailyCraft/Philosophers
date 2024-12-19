/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:50:40 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 18:41:23 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->data->forks;
	pthread_mutex_lock(&forks[philo->id]);
	print(philo, "has taken a fork");
	if (philo->id == (philo->id + 1) % philo->data->amount)
	{
		philo_sleep(philo, philo->data->die);
		pthread_mutex_unlock(&forks[philo->id]);
		return ;
	}
	pthread_mutex_lock(&forks[(philo->id + 1) % philo->data->amount]);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	philo_sleep(philo, philo->data->eat);
	pthread_mutex_unlock(&forks[(philo->id + 1) % philo->data->amount]);
	pthread_mutex_unlock(&forks[philo->id]);
}

void	*philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stopped_mutex);
	pthread_mutex_unlock(&philo->data->stopped_mutex);
	if (philo->id % 2)
		usleep(3e3);
	while (!is_stopped(philo))
	{
		eat(philo);
		print(philo, "is sleeping");
		philo_sleep(philo, philo->data->sleep);
		print(philo, "is thinking");
	}
	return (NULL);
}
