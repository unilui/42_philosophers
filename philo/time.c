/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/22 20:57:01 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	current_time(pthread_mutex_t *time_mtx)
{
	static size_t	initial_time;
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	pthread_mutex_lock(time_mtx);
	if (!initial_time)
		initial_time = time;
	pthread_mutex_unlock(time_mtx);
	return (time - initial_time);
}

int	simulation_status(t_philo *ph)
{
	int	status;

	pthread_mutex_lock(ph->simulation_mtx);
	status = *ph->simulation;
	pthread_mutex_unlock(ph->simulation_mtx);
	return (status);
}
