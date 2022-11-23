/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:20:23 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/23 15:39:07 by lufelip2         ###   ########.fr       */
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
	int				holding_fork;
	int				nop;
	char			*forks;
	int				*simulation;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	*simulation_mtx;
	pthread_mutex_t	*print_mtx;
	pthread_mutex_t	*time_mtx;
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
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	time_mtx;
}	t_data;

void	thinking(t_philo *ph);
void	eating(t_philo *ph);
void	sleeping(t_philo *ph);
void	return_forks(t_philo *ph);
void	put_message(t_philo *ph, char *message);
void	call_waitress(t_philo *ph);
void	*ft_calloc(size_t nmemb, size_t size);
int		simulation_status(t_philo *ph);
void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int c);
long	ft_atoi(const char *nptr);
int		args_validation(int argc, char **argv);
int		init_simulation(int argc, char **argv, t_data *data);
void	*philosopher(void *args);
size_t	current_time(pthread_mutex_t *time_mtx);
void	*cardiac_monitor(void *args);
void	*waitress(void *args);
void	create_threads(t_data *data);
void	init_philosophers(t_data *data);
void	init_mtx(t_data *data);
void	init_forks(t_data *data);
void	destroy_mtx(t_data *data);
void	wait_threads(t_data *data);
void	free_memory(t_data *data);

#endif
