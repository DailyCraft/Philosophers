/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 07:50:40 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/17 16:59:46 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_t	*forks;

	forks = philo->data->forks;
	pthread_mutex_lock(&forks[philo->id]);
	log(philo, "has taken a fork");
	pthread_mutex_lock(&forks[(philo->id + 1) % philo->data->amount]);
	log(philo, "has taken a fork");
	log(philo, "is eating");
	usleep(philo->data->sleep * 1e3);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	pthread_mutex_unlock(&forks[philo->id]);
	pthread_mutex_unlock(&forks[(philo->id + 1) % philo->data->amount]);
}

void	*action(t_philo *philo)
{
	philo->eat_count = 0;
	if (philo->id % 2)
		usleep(15000);
	while (!philo->data->stopped)
	{
		eat(philo);
		if (philo->data->stopped)
			break ;
		log(philo, "is sleeping");
		usleep(philo->data->sleep * 1e3);
		log(philo, "is thinking");
	}
	return (NULL);
}
