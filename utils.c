/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:05:59 by mgamraou          #+#    #+#             */
/*   Updated: 2025/06/29 18:57:21 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	ft_usleep(long sleep_time, t_table *table)
{
	long	start;

	start = get_time();
	while (get_time() - start < sleep_time)
	{
		if (sim_finished(table))
			break ;
		usleep(10);
	}
}
