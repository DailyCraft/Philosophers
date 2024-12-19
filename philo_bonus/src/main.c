/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:29:43 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/19 22:58:18 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	create_forks(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->amount)
	{
		pid = fork();
		if (pid == 0)
			return (i);
		if (pid == -1)
			return (-2);
		data->child_pids[i] = pid;
		i++;
	}
	return (-1);
}

void	killall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount && data->child_pids[i])
		kill(data->child_pids[i++], SIGTERM);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		init;
	int		id;
	int		status;

	init = init_data(&data, argc, argv);
	if (init == 0)
	{
		init = write(2, "Invalid arguments!\n", 19);
		return (1);
	}
	id = create_forks(&data);
	if (id == -2)
	{
		killall(&data);
		free_data(&data, 1);
		write(2, "Failed to create processes for all philosophers!\n", 49);
		return (1);
	}
	else if (id == -1)
	{
		sem_post(data.stopped);
		waitpid(-1, &status, 0);
		killall(&data);
		free_data(&data, 1);
	}
	else
	{
		free(data.child_pids);
		data.philo.id = id;
		philo(&data);
		free_data(&data, 0);
	}
}
