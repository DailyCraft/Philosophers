/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:13:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/20 12:15:50 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->eat_amount = -1;
	if (!parse(data, argc, argv))
		return (0);
	sem_unlink("philo_forks");
	sem_unlink("philo_writing");
	sem_unlink("philo_eat");
	sem_unlink("philo_start");
	sem_unlink("philo_stopped");
	data->forks = sem_open("philo_forks", O_CREAT, S_IRWXU, data->amount);
	data->writing = sem_open("philo_writing", O_CREAT, S_IRWXU, 1);
	data->all_ate = sem_open("philo_eat", O_CREAT, S_IRWXU, 0);
	data->start = sem_open("philo_start", O_CREAT, S_IRWXU, 0);
	data->stopped = sem_open("philo_stopped", O_CREAT, S_IRWXU, 0);
	data->philo.eat_count = 0;
	data->philo.stopped = 0;
	data->child_pids = malloc(data->amount * sizeof(int));
	memset(data->child_pids, 0, data->amount * sizeof(int));
	return (1);
}

void	free_data(t_data *data, int unlink)
{
	if (data->child_pids)
		free(data->child_pids);
	sem_close(data->forks);
	sem_close(data->writing);
	sem_close(data->all_ate);
	sem_close(data->start);
	sem_close(data->stopped);
	if (unlink)
	{
		sem_unlink("philo_forks");
		sem_unlink("philo_writing");
		sem_unlink("philo_eat");
		sem_unlink("philo_start");
		sem_unlink("philo_stopped");
	}
}
