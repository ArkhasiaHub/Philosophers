/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:21:17 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 13:34:44 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	create_philo(t_program *p, t_philo *philo, int id);
static void	init_philo(t_philo *philo, int id);
static void	assign_forks(t_program *p, t_philo *philo);
static int	alloc_program(t_program *p);

int	init_program(t_program *p)
{
	int	i;

	if (alloc_program(p))
		return (1);
	if (pthread_mutex_init(&(p->mutex), NULL) != 0)
		return (free_program(p, false, false), 1);
	if (pthread_mutex_init(&(p->write_mutex), NULL) != 0)
		return (free_program(p, true, false), 1);
	i = -1;
	while (++i < p->nb_philo)
	{
		p->forks[i].taken = false;
		if (pthread_mutex_init(&(p->philos[i].mutex), NULL) != 0)
			return (destroy_mutex(p, i, i), free_program(p, true, true), 1);
		if (pthread_mutex_init(&(p->forks[i].mutex), NULL) != 0)
			return (destroy_mutex(p, i + 1, i), free_program(p, true, true), 1);
		create_philo(p, p->philos + i, i + 1);
		p->forks->id = i;
	}
	return (0);
}

static int	alloc_program(t_program *p)
{
	p->end_program = false;
	p->threads_ready = false;
	p->forks = ft_calloc(p->nb_philo + 1, sizeof(t_fork));
	if (!p->forks)
		return (1);
	p->philos = ft_calloc(p->nb_philo + 1, sizeof(t_philo));
	if (!p->philos)
		return (free(p->forks), 1);
	return (0);
}

static void	create_philo(t_program *p, t_philo *philo, int id)
{
	init_philo(philo, id);
	assign_forks(p, philo);
	philo->program = p;
}

static void	init_philo(t_philo *philo, int id)
{
	philo->count_meal = 0;
	philo->id = id;
	philo->is_full = false;
	philo->died = false;
	philo->last_eat_time = 0;
}

static void	assign_forks(t_program *p, t_philo *philo)
{
	int	pos;

	pos = philo->id;
	philo->right_fork = &(p->forks[pos - 1]);
	philo->left_fork = &(p->forks[pos % p->nb_philo]);
}
