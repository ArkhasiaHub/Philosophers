/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:00 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 13:22:39 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong input.\n", 14);
		return (1);
	}
	if (parse_input(&program, argc, argv))
		return (1);
	if (init_program(&program))
		return (1);
	dinner_start(&program);
	destroy_mutex(&program, program.nb_philo, program.nb_philo);
	free_program(&program, true, true);
	return (0);
}
