/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:57:29 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/28 10:49:35 by mgamraou         ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int	fork_id;
}	t_fork;

typedef struct s_philo
{
	int	id;
	long	meals_counter;
	bool	full;
	long	last_meal_time;
	t_fork	*l_fork;
	t_fork	*r_fork;
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
	bool	end_sim;
	t_fork	*forks;
	t_philo	*philos;
};

void	parse_input(t_table *table, char **av);
char	*valid_str(char *str);
long	ft_atol(char *str);
void	error_exit(char *str);

#endif
