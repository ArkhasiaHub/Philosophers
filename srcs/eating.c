/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:11:03 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 11:28:26 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	get_left_fork(t_philo *philo);
static bool	get_right_fork(t_philo *philo);

void	eating(t_philo *philo)
{
	long	current_time;

	if (get_left_fork(philo))
		return ;
	if (get_right_fork(philo))
		return ;
	current_time = get_time(philo->program, MILLISECOND);
	set_long(&(philo->mutex), \
		current_time, &(philo->last_eat_time));
	philo->count_meal += 1;
	philo_status(philo, EATING);
	if (philo->count_meal == philo->program->nb_meals)
		set_bool(&(philo->mutex), true, \
		&(philo->is_full));
	if (philo->program->time_eat >= philo->program->time_die)
	{
		while (!had_philo_died(philo))
			;
		philo_status(philo, DIED);
		set_bool(&(philo->mutex), true, &(philo->died));
	}
	else
		usleep(philo->program->time_eat);
	set_bool(&(philo->left_fork->mutex), false, &(philo->left_fork->taken));
	set_bool(&(philo->right_fork->mutex), false, &(philo->right_fork->taken));
}

static bool	get_left_fork(t_philo *philo)
{
	while (get_bool(&(philo->left_fork->mutex), &(philo->left_fork->taken)))
	{
		if (check_philo(philo->program))
			return (true);
		if (had_philo_died(philo))
		{
			philo_status(philo, DIED);
			set_bool(&(philo->mutex), true, &(philo->died));
			return (true);
		}
	}
	set_bool(&(philo->left_fork->mutex), true, &(philo->left_fork->taken));
	philo_status(philo, LEFT_FORK);
	return (false);
}

static bool	get_right_fork(t_philo *philo)
{
	while (get_bool(&(philo->right_fork->mutex), &(philo->right_fork->taken)))
	{
		if (check_philo(philo->program))
			return (true);
		if (had_philo_died(philo))
		{
			philo_status(philo, DIED);
			set_bool(&(philo->mutex), true, &(philo->died));
			return (true);
		}
	}
	set_bool(&(philo->right_fork->mutex), true, &(philo->right_fork->taken));
	philo_status(philo, RIGHT_FORK);
	return (false);
}
