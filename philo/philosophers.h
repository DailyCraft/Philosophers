/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:14:34 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/13 15:59:34 by dvan-hum         ###   ########.fr       */
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

typedef struct s_data
{
	pthread_t		*threads;

	int				amount;
	int				die;
	int				eat;
	int				sleep;
	int				eat_amount;

	pthread_mutex_t	forks_mutex;
	int				*forks_owner;
	pthread_mutex_t	stopped_mutex;
	int				stopped;
	pthread_mutex_t	satiated_mutex;
	int				*satiated;
}	t_data;

void	*action(t_data *data);
int		secure_atoi(char *str, int *err);
long	get_time(void);
int		*get_fork(t_data *data, int index);
int		is_stopped(t_data *data);
void	stoppable_mssleep(t_data *data, unsigned int ms);

#endif