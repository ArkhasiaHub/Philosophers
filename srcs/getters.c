/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:20:55 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 13:27:43 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	get_bool(t_mutex *mutex, bool *src)
{
	bool	dest;

	pthread_mutex_lock(mutex);
	dest = *src;
	pthread_mutex_unlock(mutex);
	return (dest);
}

long	get_long(t_mutex *mutex, long *src)
{
	long	dest;

	pthread_mutex_lock(mutex);
	dest = *src;
	pthread_mutex_unlock(mutex);
	return (dest);
}

int	get_int(t_mutex *mutex, int *src)
{
	int	dest;

	pthread_mutex_lock(mutex);
	dest = *src;
	pthread_mutex_unlock(mutex);
	return (dest);
}

long	get_time(t_program *p, int time_code)
{
	struct timeval	tv;

	(void)p;
	gettimeofday(&tv, NULL);
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (-1);
}
