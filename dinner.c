/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:03:19 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/30 12:32:12 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static void	thinking_sim(t_philo *philo)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	print_status(THINKING, philo);
	if (philo->table->philo_num % 2 == 0)
		return ;
	time_to_eat = philo->table->time_to_eat;
	time_to_sleep = philo->table->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	ft_usleep(time_to_think, philo->table);
}

void	*one_philo(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	increment_long(&philo->table->table_mutex, &philo->table->threads_running);
	print_status(TAKEN_A_FORK, philo);
	while (!sim_finished(philo->table))
		ft_usleep(philo->table->time_to_sleep, philo->table);
	return (NULL);
}

static void	eat_sim(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(TAKEN_A_FORK, philo);
	pthread_mutex_lock(philo->second_fork);
	print_status(TAKEN_A_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	philo->meals_counter++;
	print_status(EATING, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_limit_meals > 0 && philo->meals_counter == philo->table->num_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time());
	increment_long(&philo->table->table_mutex, &philo->table->threads_running);
	while (!sim_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat_sim(philo);
		print_status(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking_sim(philo);
	}
	return (NULL);
}

//WARNING: sim must insta stop after philo eaten number of meals needed (dont wait for routine to end)

void	start_sim(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_limit_meals == 0)
		return ;
	else if (table->philo_num == 1)
		pthread_create(&table->philos[0].thread_id, NULL, one_philo, &table->philos[0]);
	else
	{
		while (i < table->philo_num)
		{
			pthread_create(&table->philos[i].thread_id, NULL, simulation, &table->philos[i]);
			i++;
		}
	}
	pthread_create(&table->monitor, NULL, monitor_sim, table);
	table->start_sim = get_time();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_num)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_sim, true);
	pthread_join(table->monitor, NULL);
}
