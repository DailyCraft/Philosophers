/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:06:54 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 22:20:52 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	print(t_data *data, char *action)
{
	sem_wait(data->writing);
	printf("%ld %d %s\n", get_time(), data->philo.id + 1, action);
	sem_post(data->writing);
}
