/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:25:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/16 14:26:16 by dvan-hum         ###   ########.fr       */
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

typedef struct s_data
{
	int	amount;
	int	die;
	int	eat;
	int	sleep;
	int	eat_amount;
}	t_data;

int	ft_clear_atoi(const char *str, int *unclear);

#endif