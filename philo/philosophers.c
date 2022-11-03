/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/02 21:46:03 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

//pthread_create -> ok
//pthread_detach
//pthread_join
//pthread_mutex_init
//pthread_mutex_destroy
//pthread_mutex_lock
//pthread_mutex_unlock


size_t	current_time(void)
{
	static size_t	initial_time;
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	if (!initial_time)
		initial_time = time;
	return (time - initial_time);
}

void	*philo()
{
	int	time_to_die;
	int

	time_to_die = 200;
	while(current_time() < time_to_die)
	{
		
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	th;
	//int			i;

	// i = 0;
	// while (i < 5)
	pthread_create(&th, NULL, &philo, NULL);
	// i = 0;
	// while (i < 5)
	pthread_join(th, NULL);
	return (0);
}
