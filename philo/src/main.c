/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:17:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 18:45:15 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	stop(t_data *data)
{
	pthread_mutex_lock(&data->stopped_mutex);
	data->stopped = 1;
	pthread_mutex_unlock(&data->stopped_mutex);
}

static void	check_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->eat_mutex);
	if (get_time() - philo->last_eat >= data->die)
	{
		print(philo, "died");
		stop(data);
	}
	pthread_mutex_unlock(&data->eat_mutex);
}

static void	check_simulation(t_data *data)
{
	int	i;

	while (!data->stopped)
	{
		i = 0;
		while (i < data->amount && !data->stopped)
		{
			check_eat(data, data->philos + i);
			usleep(100);
			i++;
		}
		if (data->stopped || data->eat_amount == -1)
			continue ;
		i = 0;
		pthread_mutex_lock(&data->eat_mutex);
		while (i < data->amount)
		{
			if (data->philos[i].eat_count < data->eat_amount)
				break ;
			i++;
		}
		pthread_mutex_unlock(&data->eat_mutex);
		if (i == data->amount)
			stop(data);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		init;

	init = init_data(&data, argc, argv);
	if (init == 1)
	{
		init = write(2, "Failed to create threads for all philosophers!\n", 47);
		free_data(&data, 1);
		return (1);
	}
	else if (init == 2)
	{
		init = write(2, "Invalid arguments!\n", 19);
		return (1);
	}
	check_simulation(&data);
	free_data(&data, 0);
}
