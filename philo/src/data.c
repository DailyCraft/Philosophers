/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:16:24 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/18 11:50:29 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philos(t_data *data)
{
	long	current;
	int		i;

	current = get_time();
	i = 0;
	while (i < data->amount)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = current;
		i++;
	}
}

static int	init_threads_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0
			|| pthread_create(data->threads + i, NULL,
				(void *(*)(void *)) philo, data->philos + i) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->stopped = 0;
	data->eat_amount = -1;
	if (!parse(data, argc, argv))
		return (2);
	data->threads = ft_calloc(data->amount, sizeof(pthread_t));
	data->forks = ft_calloc(data->amount, sizeof(pthread_mutex_t));
	data->philos = malloc(data->amount * sizeof(t_philo));
	pthread_mutex_init(&data->stopped_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	init_philos(data);
	pthread_mutex_lock(&data->stopped_mutex);
	return (!init_threads_mutex(data));
}

void	free_data(t_data *data, int detach_threads)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (detach_threads)
			pthread_detach(data->threads[i++]);
		else
			pthread_join(data->threads[i++], NULL);
	}
	pthread_mutex_destroy(&data->stopped_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	free(data->threads);
	free(data->forks);
	free(data->philos);
}