/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:11:29 by ade-agui          #+#    #+#             */
/*   Updated: 2022/09/04 12:11:30 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *ptr)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (ptr[i] == ' ' || (ptr[i] >= '\t' && ptr[i] <= '\r' ))
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = ptr[i] - '0' + (res * 10);
		i++;
	}
	return (res * sign);
}

double	philos_atoi(const char *ptr)
{
	double	number;

	number = 0;
	while (ft_isdigit(*ptr))
	{
		number *= 10;
		number += (*ptr - '0');
		ptr++;
	}
	return (number);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (milliseconds);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_s;
	size_t			i;

	i = 0;
	s_s = (unsigned char *)s;
	while (i < n)
	{
		s_s[i] = '\0';
		i++;
	}
}
