/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:29:43 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/16 14:38:20 by dvan-hum         ###   ########.fr       */
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

static int	create_forks(int amount)
{
	int	i;
	int	pid;

	pid = fork();
	i = 1;
	while (pid != 0 && i < amount)
	{
		pid = fork();
		i++;
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	t_data	data;
	sem_t	*sem;

	data.eat_amount = -1;
	if (!parse(&data, argc, argv))
		return (0);
	sem = sem_open("philo_forks", O_CREAT, S_IRUSR | S_IWUSR, data.amount);
	if (create_forks(data.amount) != 0)
	{
		waitpid(-1, NULL, 0);
		sem_close(sem);
		sem_unlink("philo_forks");
	}
	else
	{
		sem_post(sem);
		sem_close(sem);
	}
}
