/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:17 by sbriche           #+#    #+#             */
/*   Updated: 2023/12/20 11:43:07 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static size_t	move_i(const char *nptr)
{
	size_t	i;

	i = 0;
	while (is_space(nptr[i]) == 1)
		i++;
	if (nptr[i] == '+')
		i++;
	return (i);
}

static long	protect_i(long nb, int sign)
{
	long	test;

	test = nb;
	test *= 10;
	test /= 10;
	if (test != nb && sign == 1)
		return (-1);
	if (test != nb && sign == -1)
		return (0);
	return (1);
}

long	ft_atol(const char *nptr)
{
	int		sign;
	long	res;
	size_t	i;

	res = 0;
	sign = 1;
	i = 0;
	i = move_i(nptr);
	if (nptr[i] == '-' && nptr[i - 1] != '+' && nptr[i -1 != '-'])
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) == 1)
	{
		if (protect_i(res, sign) == -1 || \
			protect_i(res, sign) == 0)
			return (protect_i(res, sign));
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}
