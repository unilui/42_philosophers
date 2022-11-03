/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/03 07:41:51 by lufelip2         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	char			*forks;
	int				*simulation;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	*simulation_mtx;
	pthread_mutex_t	philo_mtx;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				simulation;
	char			*forks;
	pthread_mutex_t	*fork_mtx;
	pthread_t		cm;
	pthread_t		*th;
	t_philo			*ph;
	pthread_mutex_t	simulation_mtx;
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

int	simulation_status(t_philo *ph)
{
	int status;
	pthread_mutex_lock(ph->simulation_mtx);
	status = *ph->simulation;
	pthread_mutex_unlock(ph->simulation_mtx);
	return (status);
}

void	*philosopher(void *args)
{
	t_philo *info;

	info = (t_philo *)args;
	while (simulation_status(info) == RUNNING)
	{
		printf("%zu: %d is thinking\n", current_time(), info->id + 1);
		//while (!get_forks(info->left_fork, info->right_fork))
		//	continue;
		if (simulation_status(info) == STOP)
			break ;
		printf("%zu: %d is eating\n", current_time(), info->id + 1);
		usleep(info->time_to_eat * 1000);
		//meal_register(info->id);
		//return_forks(info->left_fork, info->right_fork);
		if (simulation_status(info) == STOP)
			break ;
		printf("%zu: %d is sleeping\n", current_time(), info->id + 1);
		usleep(info->time_to_sleep * 1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	id;

	id = 0;
	data->th = malloc(data->number_of_philosophers * sizeof(pthread_t));
	while (id < data->number_of_philosophers)
	{
		pthread_create(&data->th[id],
			NULL, &philosopher, (void *)&data->ph[id]);
		id++;
	}
}

void	create_philosophers(t_data *data)
{
	int	id;

	id = 0;
	data->ph = malloc(data->number_of_philosophers * sizeof(t_philo));
	while (id < data->number_of_philosophers)
	{
		data->ph[id].simulation = &data->simulation;
		data->ph[id].simulation_mtx = &data->simulation_mtx;
		data->ph[id].time_to_die = data->time_to_die;
		data->ph[id].time_to_eat = data->time_to_eat;
		data->ph[id].time_to_sleep = data->time_to_sleep;
		data->ph[id].forks = data->forks;
		data->ph[id].fork_mtx = data->fork_mtx;
		data->ph[id].id = id;
		id++;
	}
}

void	init_simulation(t_data *data)
{
	data->number_of_philosophers = 4;
	data->time_to_die = 800;
	data->time_to_eat = 200;
	data->time_to_sleep = 200;
	data->simulation = RUNNING;
}

void	init_mtx(t_data *data)
{
	int	id;
	int	nbr;

	id = 0;
	nbr = data->number_of_philosophers;
	pthread_mutex_init(&data->simulation_mtx, NULL);
	while (id < nbr)
	{
		pthread_mutex_init(&data->ph[id].philo_mtx, NULL);
		id ++;
	}
	id = 0;
	while (id < (nbr + (nbr == 1)))
	{
		pthread_mutex_init(&data->fork_mtx[id], NULL);
		id ++;
	}
}

void	destroy_mtx(t_data *data)
{
	int	id;
	int	nbr;

	id = 0;
	nbr = data->number_of_philosophers;
	pthread_mutex_destroy(&data->simulation_mtx);
	while (id < nbr)
	{
		pthread_mutex_destroy(&data->ph[id].philo_mtx);
		id ++;
	}
	id = 0;
	while (id < (nbr + (nbr == 1)))
	{
		pthread_mutex_destroy(&data->fork_mtx[id]);
		id ++;
	}
}

void	*cardiac_monitor(void *args)
{
	int		id;
	size_t	time;
	t_data	*data;

	id = 0;
	data = (t_data *)args;
	while (id < data->number_of_philosophers
			&& data->simulation == RUNNING)
	{
		time = current_time();
		pthread_mutex_lock(&data->simulation_mtx);
		pthread_mutex_lock(&data->ph[id].philo_mtx);
		if (time > data->ph[id].time_to_die)
		{
			data->simulation = STOP;
			printf("%zu: %d is died\n", time, id + 1);
		}
		pthread_mutex_unlock(&data->ph[id].philo_mtx);
		pthread_mutex_unlock(&data->simulation_mtx);
		id++;
		if (id == data->number_of_philosophers)
			id = 0;
	}
	return (NULL);
}

void	init_services(t_data *data)
{
	pthread_create(&data->cm, NULL, &cardiac_monitor, (void *)data);
}

void	wait_threads(t_data *data)
{
	int	id;

	id = 0;
	pthread_join(data->cm, NULL);
	while (id < data->number_of_philosophers)
	{
		pthread_join(data->th[id], NULL);
		id++;
	}
}

void	create_forks(t_data *data)
{
	int	nbr;

	nbr = data->number_of_philosophers;
	data->forks = malloc((nbr * sizeof(char)) + (nbr == 1));
	data->fork_mtx = malloc((nbr * sizeof(pthread_mutex_t)) + (nbr == 1));
	memset(&data->forks, 0, nbr + (nbr == 1));
	memset(&data->forks, 1, nbr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_simulation(&data);
	create_philosophers(&data);
	create_forks(&data);
	init_mtx(&data);
	create_threads(&data);
	init_services(&data);
	wait_threads(&data);
	destroy_mtx(&data);
	return (0);
}
