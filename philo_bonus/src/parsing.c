/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:13:59 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 22:14:00 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	parse_args(int *value, char *arg)
{
	int	err;

	*value = ft_clear_atoi(arg, &err);
	err += *value < 1;
	return (!err);
}

int	parse(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s <number_of_philosophers> ", argv[0]);
		printf("<time_to_die> <time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	return (parse_args(&data->amount, argv[1])
		&& parse_args(&data->die, argv[2])
		&& parse_args(&data->eat, argv[3])
		&& parse_args(&data->sleep, argv[4])
		&& (argc == 5 || parse_args(&data->eat_amount, argv[5])));
}
