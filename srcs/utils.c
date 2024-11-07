/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:44 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 13:27:54 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_program *p, int nb_philo, int nb_fork)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&(p->philos[i].mutex));
	i = -1;
	while (++i < nb_fork)
		pthread_mutex_destroy(&(p->forks[i].mutex));
}

void	free_program(t_program *p, bool p_mutex, bool w_mutex)
{
	if (p->forks)
		free(p->forks);
	if (p->philos)
		free(p->philos);
	if (p_mutex)
		pthread_mutex_destroy(&(p->mutex));
	if (w_mutex)
		pthread_mutex_destroy(&(p->write_mutex));
}

bool	check_philo(t_program *p)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < p->nb_philo)
	{
		philo = p->philos + i;
		if (get_bool(&(philo->mutex), &(philo->died)))
			return (true);
	}
	return (false);
}

void	philo_status(t_philo *philo, int status)
{
	t_program	*p;
	long		time;

	p = philo->program;
	pthread_mutex_lock(&(p->write_mutex));
	if (check_philo(p))
	{
		pthread_mutex_unlock(&(p->write_mutex));
		return ;
	}
	time = get_time(p, MILLISECOND) - p->start_time;
	if (status == LEFT_FORK)
		printf("%ld philo %d take left fork.\n", time, philo->id);
	else if (status == RIGHT_FORK)
		printf("%ld philo %d take right fork.\n", time, philo->id);
	else if (status == EATING)
		printf("%ld philo %d is eating.\n", time, philo->id);
	else if (status == THINKING)
		printf("%ld philo %d is thinking.\n", time, philo->id);
	else if (status == SLEEPING)
		printf("%ld philo %d is sleeping.\n", time, philo->id);
	else if (status == DIED)
		printf("%ld philo %d died.\n", time, philo->id);
	pthread_mutex_unlock(&(p->write_mutex));
}

bool	is_dinner_finish(t_program *p)
{
	return (get_bool(&(p->mutex), &(p->end_program)));
}
