/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:29:43 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/20 15:38:48 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	killall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->amount && data->child_pids[i])
		kill(data->child_pids[i++], SIGTERM);
}

static int	create_forks(t_data *data, int *id)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->amount)
	{
		pid = fork();
		if (pid == -1)
		{
			killall(data);
			free_data(data, 1);
			i = write(2, "Failed to create processes for all philosophers!\n", 49);
			return (0);
		}
		data->child_pids[i] = pid;
		if (pid == 0)
		{
			*id = i;
			return (1);
		}
		i++;
	}
	*id = -1;
	return (1);
}

static void	start_parent(t_data *data)
{
	int	i;

	sem_post(data->start);
	if (data->eat_amount == -1)
	{
		i = 0;
		while (i < data->amount)
		{
			waitpid(-1, NULL, 0);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < data->amount - 1)
		{
			sem_wait(data->all_ate);
			i++;
		}
		sem_wait(data->writing);
		stop(data);
	}
	free_data(data, 1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		id;

	if (!init_data(&data, argc, argv) || !create_forks(&data, &id))
		return (1);
	if (id == -1)
		start_parent(&data);
	else
	{
		(free(data.child_pids), data.child_pids = NULL);
		data.philo.id = id;
		philo(&data);
		free_data(&data, 0);
	}
}
