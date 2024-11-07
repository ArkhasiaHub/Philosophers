/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:29 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 11:26:33 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	had_philo_died(t_philo *philo)
{
	long	time;
	long	time_passed;

	if (get_bool(&(philo->mutex), &(philo->is_full)))
		return (false);
	time = get_time(philo->program, MILLISECOND);
	time_passed = time - get_long(&(philo->mutex), &(philo->last_eat_time));
	if (time_passed >= (philo->program->time_die / 1e3))
		return (true);
	return (false);
}

void	check_philo_died(t_philo *philo)
{
	if (had_philo_died(philo))
	{
		philo_status(philo, DIED);
		set_bool(&(philo->mutex), true, &(philo->died));
	}
}
