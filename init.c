/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:37:37 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/28 12:01:00 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_num;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		if (philo->id == philo_nbr)
			philo->second_fork = &forks[0];
		else
			philo->second_fork = &forks[philo->id];
	}
	else
	{
		philo->second_fork = &forks[i];
		if (philo->id == philo_nbr)
			philo->first_fork = &forks[0];
		else
			philo->first_fork = &forks[philo->id];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	while (++i < table->philo_num)
		pthread_mutex_init(&table->forks[i], NULL);
	philo_init(table);
}
