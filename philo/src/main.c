/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:17:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/11 11:40:29 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_args(int *value, char *arg)
{
	int	err;

	*value = secure_atoi(arg, (err = 0, &err));
	if (!err && *value < 1)
		err = 1;
	return (!err);
}

static int	parse(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s <number_of_philosophers> ", argv[0]);
		printf("<time_to_die> <time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (!parse_args(&data->amount, argv[1])
		|| !parse_args(&data->die, argv[2])
		|| !parse_args(&data->eat, argv[3])
		|| !parse_args(&data->sleep, argv[4])
		|| (argc == 6 && !parse_args(&data->eat_amount, argv[5])))
	{
		printf("Invalid argument!\n");
		return (0);
	}
	return (1);
}

static int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		if (pthread_create(data->threads + i, NULL,
				(void *(*)(void *)) action, data) != 0)
		{
			i = 0;
			while (data->threads[i])
			{
				pthread_detach(data->threads[i]);
				i++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse(&data, argc, argv))
		return (0);
	data.stopped = 0;
	data.eat_amount = -1;
	data.forks_owner = malloc(data.amount * sizeof(int));
	data.threads = malloc(data.amount * sizeof(pthread_t));
	memset(data.forks_owner, 0, data.amount * sizeof(int));
	memset(data.threads, 0, data.amount * sizeof(pthread_t));
	pthread_mutex_init(&data.forks_mutex, NULL);
	pthread_mutex_init(&data.stopped_mutex, NULL);
	if (init_threads(&data))
		join_threads(&data);
	else
		printf("Failed to create threads for all philosophers!\n");
	pthread_mutex_destroy(&data.forks_mutex);
	pthread_mutex_destroy(&data.stopped_mutex);
	free(data.forks_owner);
	free(data.threads);
}