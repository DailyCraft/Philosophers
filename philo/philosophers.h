/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:14:34 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/17 16:57:51 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	long	last_eat;
	int		eat_count;
	t_data	*data;
}	t_philo;

struct s_data
{
	int				amount;
	int				die;
	int				eat;
	int				sleep;
	int				eat_amount;

	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	int				stopped;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	write_mutex;
};

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_clear_atoi(const char *str, int *unclear);

void	*action(t_philo *data);

long	get_time(void);
void	smart_sleep(t_data *data, unsigned int ms);
void	log(t_philo *philo, char *action);

#endif