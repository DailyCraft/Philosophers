/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:19:28 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/29 08:56:55 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*wait_philo(t_data *data)
{
	waitpid(-1, NULL, 0);
	data->philo.stopped = 1;
	sem_post(data->parent_sem);
	return (NULL);
}

static void	*ate_check(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->amount)
		sem_wait(data->all_ate);
	sem_wait(data->writing);
	usleep(1000);
	if (!data->philo.stopped)
		stop(data);
	else
		sem_post(data->writing);
	sem_post(data->parent_sem);
	return (NULL);
}

void	parent(t_data *data)
{
	pthread_t	wait_thread;
	pthread_t	ate_thread;
	int			i;

	data->philo.stopped = 0;
	sem_post(data->start);
	sem_unlink("philo_parent");
	data->parent_sem = sem_open("philo_parent", O_CREAT, S_IRWXU, 0);
	pthread_create(&wait_thread, NULL, (void *(*)(void *)) wait_philo, data);
	pthread_create(&ate_thread, NULL, (void *(*)(void *)) ate_check, data);
	sem_wait(data->parent_sem);
	i = -1;
	while (++i < data->amount)
		sem_post(data->all_ate);
	pthread_join(wait_thread, NULL);
	pthread_join(ate_thread, NULL);
	sem_close(data->parent_sem);
	sem_unlink("philo_parent");
}
