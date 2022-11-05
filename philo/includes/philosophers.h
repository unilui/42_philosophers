/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:20:23 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/03 07:29:39 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

# define RUNNING 1
# define STOP 0

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
	t_philo			*ph;
	pthread_t		wt;
	pthread_t		cm;
	pthread_t		*th;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	simulation_mtx;
}	t_data;

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	*philosopher(void *args);
size_t	current_time(void);
void	*cardiac_monitor(void *args);
void	*waitress(void *args);
void	create_threads(t_data *data);
void	create_philosophers(t_data *data);
void	init_mtx(t_data *data);
void	init_services(t_data *data);
void	create_forks(t_data *data);
void	destroy_mtx(t_data *data);
void	wait_threads(t_data *data);

#endif
