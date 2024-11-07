/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:19:05 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 11:27:33 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	check_philo_died(philo);
	philo_status(philo, THINKING);
}

void	sleeping(t_philo *philo)
{
	if (philo->program->time_sleep >= philo->program->time_die)
	{
		while (!had_philo_died(philo))
			;
		philo_status(philo, DIED);
		set_bool(&(philo->mutex), true, &(philo->died));
	}
	else
	{
		philo_status(philo, SLEEPING);
		usleep(philo->program->time_sleep);
	}
}

void	*dinner_run(void *ptr)
{
	t_philo		*philo;
	t_program	*p;

	philo = (t_philo *)ptr;
	p = philo->program;
	wait_all_threads(p);
	set_long(&(philo->mutex), \
		get_time(philo->program, MILLISECOND), &(philo->last_eat_time));
	if (philo->id % 2 == 0)
		usleep(p->time_die / 2);
	while (!check_philo(p) && !is_dinner_finish(p))
	{
		eating(philo);
		if (check_philo(p) || philo->is_full)
			break ;
		check_philo_died(philo);
		sleeping(philo);
		if (check_philo(p))
			break ;
		thinking(philo);
		if (check_philo(p))
			break ;
		check_philo_died(philo);
	}
	return (NULL);
}

void	dinner_start(t_program *p)
{
	t_philo	*philo;
	int		i;

	if (p->nb_meals == 0)
		return ;
	if (p->nb_philo == 1)
		pthread_create(&(p->philos->thread), NULL, one_philosopher, p->philos);
	else
	{
		i = -1;
		while (++i < p->nb_philo)
		{
			philo = p->philos + i;
			pthread_create(&(philo->thread), NULL, dinner_run, philo);
		}
	}
	p->start_time = get_time(p, MILLISECOND);
	set_bool(&(p->mutex), true, &(p->threads_ready));
	i = -1;
	while (++i < p->nb_philo)
	{
		philo = p->philos + i;
		pthread_join(philo->thread, NULL);
	}
	set_bool(&(p->mutex), true, &(p->end_program));
}
