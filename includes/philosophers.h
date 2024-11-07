/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:56:36 by sbriche           #+#    #+#             */
/*   Updated: 2024/03/21 13:24:07 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <stdint.h>

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	LEFT_FORK,
	RIGHT_FORK
}	t_philo_status;

typedef pthread_mutex_t		t_mutex;
typedef struct s_program	t_program;

typedef struct s_fork
{
	t_mutex	mutex;
	bool	taken;
	int		id;
}	t_fork;

typedef struct s_philo
{
	bool			is_full;
	int				id;
	long			count_meal;
	long			last_eat_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mutex			mutex;
	pthread_t		thread;
	t_program		*program;
	bool			died;
}	t_philo;

typedef struct s_program
{
	long		nb_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		nb_meals;
	long		start_time;
	bool		threads_ready;
	bool		end_program;
	t_fork		*forks;
	t_philo		*philos;
	t_mutex		write_mutex;
	t_mutex		mutex;
	pthread_t	monitor;
}	t_program;

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atol(const char *nptr);
void	destroy_mutex(t_program *p, int nb_philo, int nb_fork);
int		parse_input(t_program *p, int argc, char **argv);
int		init_program(t_program *p);
void	free_program(t_program *p, bool p_mutex, bool w_mutex);
void	set_bool(t_mutex *mutex, bool val, bool *dest);
void	set_long(t_mutex *mutex, long val, long *dest);
bool	get_bool(t_mutex *mutex, bool *src);
long	get_long(t_mutex *mutex, long *src);
long	get_time(t_program *p, int time_code);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
int		init_program(t_program *p);
void	wait_all_threads(t_program *p);
void	philo_status(t_philo *philo, int status);
bool	had_philo_died(t_philo *philo);
void	dinner_start(t_program *p);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	*one_philosopher(void *ptr);
bool	check_philo(t_program *p);
bool	is_dinner_finish(t_program *p);
bool	set_fork(t_mutex *mutex, bool *dest);
int		get_int(t_mutex *mutex, int *src);
void	set_int(t_mutex *mutex, int val, int *dest);
void	check_philo_died(t_philo *philo);
