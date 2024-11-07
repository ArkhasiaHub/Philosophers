/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:23:11 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 11:28:51 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating_one_philo(t_philo *philo);

void	*one_philosopher(void *ptr)
{
	t_philo		*philo;
	t_program	*p;

	philo = (t_philo *)ptr;
	p = philo->program;
	wait_all_threads(p);
	set_long(&(philo->mutex), \
		get_time(philo->program, MILLISECOND), &(philo->last_eat_time));
	while (!check_philo(p) && !is_dinner_finish(p))
	{
		eating_one_philo(philo);
		if (check_philo(p) || philo->is_full)
			break ;
		check_philo_died(philo);
		sleeping(philo);
		if (check_philo(p))
			break ;
		check_philo_died(philo);
		thinking(philo);
		if (check_philo(p))
			break ;
		check_philo_died(philo);
	}
	return (NULL);
}

static void	eating_one_philo(t_philo *philo)
{
	philo_status(philo, RIGHT_FORK);
	while (!had_philo_died(philo))
		;
	philo_status(philo, DIED);
	set_bool(&(philo->mutex), true, &(philo->died));
}
