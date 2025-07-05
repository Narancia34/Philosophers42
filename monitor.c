/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:14:46 by mgamraou          #+#    #+#             */
/*   Updated: 2025/07/01 14:23:41 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time() - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_sim(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running, table->philo_num))
		;
	while (!sim_finished(table))
	{
		if (get_long(&table->table_mutex, &table->philos_full) == table->philo_num)
			set_bool(&table->table_mutex, &table->end_sim, true);
		i = -1;
		while (++i < table->philo_num && !sim_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				print_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
