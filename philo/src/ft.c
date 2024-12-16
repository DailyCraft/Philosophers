/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:52:48 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/12/16 11:53:14 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size && nmemb > (size_t) -1 / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem)
		memset(mem, 0, nmemb * size);
	return (mem);
}

int	ft_clear_atoi(const char *str, int *unclear)
{
	unsigned int	result;
	int				neg;

	result = 0;
	neg = 1;
	*unclear = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	if (!*str)
		return (*unclear = 1, 0);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		if (result > (unsigned) 2147483647 + (neg == -1) && *unclear == 0)
			*unclear = 2;
		str++;
	}
	*unclear += *str != 0;
	return (result * neg);
}
