/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/03 02:36:37 by lufelip2         ###   ########.fr       */
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

#define RUNNING 1
#define STOP 0

typedef struct s_info
{
	int	*simulation;
	int	id;
	int	time_to_eat;
	int	time_to_sleep;
}	t_info;

typedef struct s_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			simulation;
	pthread_t	*th;
}	t_data;

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

void	*philo(void *args)
{
	t_info *info;

	info = (t_info *)args;
	while (*info->simulation == RUNNING) // Protect with mutex
	{
		printf("%zu: %d is thinking\n", current_time(), info->id);
		//while (!get_forks(info->left_fork, info->right_fork))
		//	continue;
		if (*info->simulation == STOP) // Protect with mutex
			break ;
		printf("%zu: %d is eating\n", current_time(), info->id);
		usleep(info->time_to_eat * 1000);
		//meal_register(info->id);
		//return_forks(info->left_fork, info->right_fork);
		if (*info->simulation == STOP) // Protect with mutex
			break ;
		printf("%zu: %d is sleeping\n", current_time(), info->id);
		usleep(info->time_to_sleep * 1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_create(&data->th[0], NULL, &philo, (void *)&(t_info){
		&data->simulation, 1, data->time_to_eat, data->time_to_sleep
	});
	//pthread_create(&data.th[1], NULL, &philo, (void *)&(t_info){
	//	&data.simulation, 2, data.time_to_eat, data.time_to_sleep
	//});
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.number_of_philosophers = 2;
	data.time_to_die = 800;
	data.time_to_eat = 200;
	data.time_to_sleep = 200;
	data.simulation = RUNNING;
	data.th = malloc(data.number_of_philosophers * sizeof(pthread_t));

	create_threads(&data);
	usleep(500000);
	data.simulation = STOP;
	pthread_join(data.th[0], NULL);
	pthread_join(data.th[1], NULL);
	return (0);
}
