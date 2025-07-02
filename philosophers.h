/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:57:29 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/30 12:07:33 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_table t_table;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_A_FORK,
	DIED,
}	t_philo_status;

typedef struct s_philo
{
	int	id;
	long	meals_counter;
	bool	full;
	long	last_meal_time;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	philo_mutex;
	pthread_t	thread_id;
	t_table	*table;
}	t_philo;

struct s_table
{
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_limit_meals;
	long	start_sim;
	long	threads_running;
	bool	end_sim;
	bool	all_threads_ready;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	t_philo	*philos;
	pthread_t	monitor;
};

void	parse_input(t_table *table, char **av);
char	*valid_str(char *str);
long	ft_atol(char *str);
void	error_exit(char *str);
void	init_data(t_table *table);
void	start_sim(t_table *table);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	wait_all_threads(t_table *table);
long	get_time(void);
bool	sim_finished(t_table *table);
void	ft_usleep(long sleep_time, t_table *table);
void	print_status(t_philo_status status, t_philo *philo);
void	*monitor_sim(void *data);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void	increment_long(pthread_mutex_t *mutex, long *value);

#endif
