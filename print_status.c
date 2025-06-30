/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:52:46 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/30 11:39:35 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo_status status, t_philo *philo)
{
	long	current_time;

	if (philo->full)
		return ;
	current_time = get_time() - philo->table->start_sim;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (status == TAKEN_A_FORK && !sim_finished(philo->table))
		printf("%-6ld %d has taken a fork\n", current_time, philo->id);
	else if (status == EATING && !sim_finished(philo->table))
		printf("%-6ld %d is eating\n", current_time, philo->id);
	else if (status == SLEEPING && !sim_finished(philo->table))
		printf("%-6ld %d is sleeping\n", current_time, philo->id);
	else if (status == THINKING && !sim_finished(philo->table))
		printf("%-6ld %d is thinking\n", current_time, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died", current_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
