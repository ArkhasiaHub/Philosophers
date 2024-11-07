/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:24 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 11:25:17 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_bool(t_mutex *mutex, bool val, bool *dest)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

void	set_long(t_mutex *mutex, long val, long *dest)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

void	set_int(t_mutex *mutex, int val, int *dest)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

bool	set_fork(t_mutex *mutex, bool *dest)
{
	bool	res;

	res = false;
	pthread_mutex_lock(mutex);
	if (*dest == false)
	{
		*dest = true;
		res = true;
	}
	pthread_mutex_unlock(mutex);
	return (res);
}
