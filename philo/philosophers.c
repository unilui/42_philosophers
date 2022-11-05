/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/04 21:35:41 by lufelip2         ###   ########.fr       */
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
	int				ttd;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				orders;
	char			left_fork;
	char			right_fork;
	char			*forks;
	int				*simulation;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	*simulation_mtx;
	pthread_mutex_t	philo_mtx;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				philosopher_must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				simulation;
	char			*forks;
	pthread_mutex_t	*fork_mtx;
	pthread_t		cm;
	pthread_t		wt;
	pthread_t		*th;
	t_philo			*ph;
	pthread_mutex_t	simulation_mtx;
}	t_data;

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*c;

	i = 0;
	c = (unsigned char *)s;
	while (i < n)
	{
		c[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;

	if (nmemb <= 0 || size <= 0)
		return (NULL);
	else if (size / nmemb > __INT_MAX__)
		return (NULL);
	arr = malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nmemb * size));
	return (arr);
}

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
	int	status;
	pthread_mutex_lock(ph->simulation_mtx);
	status = *ph->simulation;
	pthread_mutex_unlock(ph->simulation_mtx);
	return (status);
}

int	get_forks(t_philo *ph)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&ph->fork_mtx[ph->left_fork]);
	pthread_mutex_lock(&ph->fork_mtx[ph->right_fork]);
	if (ph->forks[ph->left_fork] && ph->forks[ph->right_fork]
		&& *ph->simulation == RUNNING)
	{
		ph->forks[ph->left_fork] = 0;
		ph->forks[ph->right_fork] = 0;
		printf("%zu: 😈 %d has taken a fork 🥢\n",
			current_time(), ph->id + 1);
		printf("%zu: 😈 %d has taken a fork 🥢\n",
			current_time(), ph->id + 1);
		status = 1;
	}
	else
	{
		pthread_mutex_unlock(&ph->fork_mtx[ph->left_fork]);
		pthread_mutex_unlock(&ph->fork_mtx[ph->right_fork]);
	}
	return (status);
}

void	return_forks(t_philo *ph)
{
	ph->forks[ph->left_fork] = 1;
	ph->forks[ph->right_fork] = 1;
	pthread_mutex_unlock(&ph->fork_mtx[ph->left_fork]);
	pthread_mutex_unlock(&ph->fork_mtx[ph->right_fork]);
}

void	call_waitress(t_philo *ph)
{
	pthread_mutex_lock(&ph->philo_mtx);
	ph->time_to_die = current_time() + ph->ttd;
	ph->orders++;
	pthread_mutex_unlock(&ph->philo_mtx);
}

void	*philosopher(void *args)
{
	t_philo *info;

	info = (t_philo *)args;
	while (simulation_status(info) == STOP)
		continue ;
	while (simulation_status(info) == RUNNING)
	{
		printf("%zu: 😈 %d is thinking 🤔\n", current_time(), info->id + 1);
		while (!get_forks(info) && simulation_status(info) == RUNNING)
			continue;
		if (simulation_status(info) == STOP)
		{
			return_forks(info);
			break ;
		}
		printf("%zu: 😈 %d is eating 🍽️\n", current_time(), info->id + 1);
		usleep(info->time_to_eat * 1000);
		call_waitress(info);
		return_forks(info);
		if (simulation_status(info) == STOP)
			break ;
		printf("%zu: 😈 %d is sleeping 😴\n", current_time(), info->id + 1);
		usleep(info->time_to_sleep * 1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	id;

	id = 0;
	data->th = ft_calloc(data->number_of_philosophers, sizeof(pthread_t));
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
	int	nbr;

	id = 0;
	nbr = data->number_of_philosophers;
	data->ph = ft_calloc(nbr, sizeof(t_philo));
	while (id < nbr)
	{
		data->ph[id].simulation = &data->simulation;
		data->ph[id].simulation_mtx = &data->simulation_mtx;
		data->ph[id].time_to_die = data->time_to_die;
		data->ph[id].ttd = data->time_to_die;
		data->ph[id].time_to_eat = data->time_to_eat;
		data->ph[id].time_to_sleep = data->time_to_sleep;
		data->ph[id].forks = data->forks;
		data->ph[id].fork_mtx = data->fork_mtx;
		data->ph[id].left_fork = id;
		if (id == (nbr - 1) && nbr > 1)
			data->ph[id].right_fork = 0;
		else
			data->ph[id].right_fork = id + 1;
		data->ph[id].id = id;
		id++;
	}
}

void	init_simulation(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philosophers = 5;
	data->time_to_die = 800;
	data->time_to_eat = 200;
	data->time_to_sleep = 200;
	data->philosopher_must_eat = 2;
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
	t_data	*data;

	id = 0;
	data = (t_data *)args;
	while (data->simulation == STOP)
		continue ;
	while (id < data->number_of_philosophers
			&& data->simulation == RUNNING)
	{
		pthread_mutex_lock(&data->simulation_mtx);
		pthread_mutex_lock(&data->ph[id].philo_mtx);
		if (current_time() > data->ph[id].time_to_die)
		{
			data->simulation = STOP;
			printf("%zu: 😵 %d died 💀\n", current_time(), id + 1);
		}
		pthread_mutex_unlock(&data->ph[id].philo_mtx);
		pthread_mutex_unlock(&data->simulation_mtx);
		id++;
		if (id == data->number_of_philosophers)
			id = 0;
	}
	return (NULL);
}

void	*waitress(void *args)
{
	int		id;
	t_data	*data;

	data = (t_data *)args;
	while (data->simulation == STOP)
		continue ;
	while (data->simulation == RUNNING)
	{
		id = 0;
		while (id < data->number_of_philosophers
			&& data->simulation == RUNNING)
		{
			if (data->ph[id].orders < data->philosopher_must_eat)
				id = 0;
			else
				id++;
		}
		pthread_mutex_lock(&data->simulation_mtx);
		data->simulation = STOP;
		pthread_mutex_unlock(&data->simulation_mtx);
	}
	return (NULL);
}

void	init_services(t_data *data)
{
	if (data->philosopher_must_eat)
		pthread_create(&data->wt, NULL, &waitress, (void *)data);
	pthread_create(&data->cm, NULL, &cardiac_monitor, (void *)data);
}

void	wait_threads(t_data *data)
{
	int	id;

	id = 0;
	pthread_join(data->cm, NULL);
	if (data->philosopher_must_eat)
		pthread_join(data->wt, NULL);
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
	data->forks = ft_calloc((nbr + (nbr == 1)), sizeof(char));
	data->fork_mtx = ft_calloc((nbr + (nbr == 1)), sizeof(pthread_mutex_t));
	nbr = 0;
	while (nbr < data->number_of_philosophers)
	{
		data->forks[nbr] = 1;
		nbr++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_simulation(&data);
	create_forks(&data);
	create_philosophers(&data);
	init_mtx(&data);
	create_threads(&data);
	init_services(&data);
	data.simulation = RUNNING;
	wait_threads(&data);
	destroy_mtx(&data);
	return (0);
}
