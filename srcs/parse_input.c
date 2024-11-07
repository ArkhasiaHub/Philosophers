/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:21:23 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 13:36:30 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_str(const char *str);
static int	is_str_num(const char *str);
static int	check_nb_meals(t_program *p, int argc, char **argv);

int	parse_input(t_program *p, int argc, char **argv)
{
	p->nb_philo = parse_str(argv[1]);
	if (p->nb_philo == -1)
		return (1);
	p->time_die = parse_str(argv[2]) * 1e3;
	if (p->time_die == -1)
		return (1);
	p->time_sleep = parse_str(argv[4]) * 1e3;
	if (p->time_sleep == -1)
		return (1);
	p->time_eat = parse_str(argv[3]) * 1e3;
	if (p->time_eat == -1)
		return (1);
	if (p->time_die < 6e4 || p->time_eat < 6e4 || \
		p->time_sleep < 6e4)
	{
		write(2, "Timestamp needs to be higher than 60ms\n", 40);
		return (1);
	}
	p->nb_meals = -1;
	if (check_nb_meals(p, argc, argv))
		return (1);
	return (0);
}

static int	check_nb_meals(t_program *p, int argc, char **argv)
{
	if (argc == 6)
	{
		p->nb_meals = parse_str(argv[5]);
		if (p->nb_meals == -1)
			return (1);
	}
	return (0);
}

static int	parse_str(const char *str)
{
	long	res;

	if (str[0] == '-')
	{
		write(2, "Strictly positives numbers accepted\n", 37);
		return (-1);
	}
	if (is_str_num(str))
	{
		write(2, "Numerical arguments needed\n", 28);
		return (-1);
	}
	res = ft_atol(str);
	if (res > INT_MAX)
	{
		write(2, "Number can't be higher to INT_MAX\n", 35);
		return (-1);
	}
	return (res);
}

static int	is_str_num(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
