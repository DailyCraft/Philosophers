/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:17:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/17 16:55:14 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_args(int *value, char *arg)
{
	int	err;

	*value = ft_clear_atoi(arg, &err);
	err += *value < 1;
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
		write(2, "Invalid argument!\n", 18);
		return (0);
	}
	return (1);
}

static void	detach_threads(t_data *data, int until, int only_mutex)
{
	int	i;

	i = 0;
	while (i < until)
	{
		if (data->threads + i && !only_mutex)
			pthread_detach(data->threads[i]);
		if (data->forks + i)
			pthread_mutex_destroy(data->forks + i);
		i++;
	}
}

void	destroy_all(t_data *data)
{
	int i;

	i = 0;
	while (i < data->amount)
		pthread_join(data->threads[i++], NULL);
	i = 0;
	while (i < data->amount)
		pthread_mutex_destroy(&data->forks[i++]);
}

void	death_checker(t_data *data)
{
	int i;

	while (!data->stopped)
	{
		i = 0;
		while (i < data->amount && !data->stopped)
		{
			pthread_mutex_lock(&data->eat_mutex);
			if (get_time() - data->philos[i].last_eat >= data->die)
			{
				pthread_mutex_lock(&data->write_mutex);
				printf("%ld %d died\n", get_time(), i + 1);
				pthread_mutex_unlock(&data->write_mutex);
				data->stopped = 1;
			}
			pthread_mutex_unlock(&data->eat_mutex);
			usleep(100);
			i++;
		}
		if (data->stopped)
			break ;
		i = 0;
		while (data->eat_amount != -1 && i < data->amount
			&& data->philos[i].eat_count >= data->eat_amount)
			i++;
		if (i == data->amount)
			data->stopped = 1;
	}
}

static int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount)
	{
		data->philos[i].id = i;
		data->philos[i].last_eat = get_time();
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0
			|| pthread_create(data->threads + i, NULL,
				(void *(*)(void *)) action, data->philos + i) != 0)
		{
			detach_threads(data, i, 0);
			return (0);
		}
		i++;
	}
	i = 0;
	death_checker(data);
	destroy_all(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.stopped = 0;
	data.eat_amount = -1;
	if (!parse(&data, argc, argv))
		return (0);
	data.threads = ft_calloc(data.amount, sizeof(pthread_t));
	data.forks = ft_calloc(data.amount, sizeof(pthread_mutex_t));
	data.philos = malloc(data.amount * sizeof(t_philo));
	pthread_mutex_init(&data.eat_mutex, NULL);
	pthread_mutex_init(&data.write_mutex, NULL);
	if (!start_simulation(&data))
		write(2, "Failed to create threads for all philosophers!\n", 47);
	pthread_mutex_destroy(&data.eat_mutex);
	pthread_mutex_destroy(&data.write_mutex);
	free(data.threads);
	free(data.forks);
	free(data.philos);
}
