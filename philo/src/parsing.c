/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:39:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/20 07:45:07 by dvan-hum         ###   ########.fr       */
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

int	parse(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s <number_of_philosophers> ", argv[0]);
		printf("<die_time> <eat_time> <sleep_time> [eat_amount]\n");
		return (0);
	}
	return (parse_args(&data->amount, argv[1])
		&& parse_args(&data->die, argv[2])
		&& parse_args(&data->eat, argv[3])
		&& parse_args(&data->sleep, argv[4])
		&& (argc == 5 || parse_args(&data->eat_amount, argv[5])));
}
