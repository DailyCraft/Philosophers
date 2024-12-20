/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:25:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/20 15:22:08 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long		last_eat;
	pthread_t	checker;
	pthread_t	stopper;
	int			stopped;
}	t_philo;

typedef struct s_data
{
	int		amount;
	int		die;
	int		eat;
	int		sleep;
	int		eat_amount;

	sem_t	*forks;
	sem_t	*writing;
	sem_t	*all_ate;
	sem_t	*start;
	sem_t	*stopped;

	t_philo	philo;
	pid_t	*child_pids;
}	t_data;

int		parse(t_data *data, int argc, char **argv);
int		init_data(t_data *data, int argc, char **argv);
void	free_data(t_data *data, int unlink);

int		ft_clear_atoi(const char *str, int *unclear);
ssize_t	ft_putnbr(long nbr);
size_t	ft_strlen(char *str);
long	get_time(void);
void	print(t_data *data, char *action);
void	philo_sleep(t_data *data, unsigned int ms);
void	stop(t_data *data);

void	philo(t_data *data);

#endif