/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:35:50 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/23 15:36:18 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *ph)
{
	if (!(ph->id % 2) && (ph->nop % 2))
		usleep(5000);
	put_message(ph, "is thinking 🤔");
}

void	eating(t_philo *ph)
{
	put_message(ph, "is eating 🍽️");
	usleep(ph->time_to_eat * 1000);
	call_waitress(ph);
	return_forks(ph);
}

void	sleeping(t_philo *ph)
{
	put_message(ph, "is sleeping 😴");
	usleep(ph->time_to_sleep * 1000);
}
