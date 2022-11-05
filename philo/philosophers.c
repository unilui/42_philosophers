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

#include "philosophers.h"

void	init_simulation(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philosophers = 5;
	data->time_to_die = 800;
	data->time_to_eat = 200;
	data->time_to_sleep = 200;
	data->philosopher_must_eat = 2;
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
