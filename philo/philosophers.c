/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/23 15:34:02 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (args_validation(argc, argv))
	{
		if (init_simulation(argc, argv, &data))
		{
			init_philosophers(&data);
			init_forks(&data);
			init_mtx(&data);
			create_threads(&data);
			wait_threads(&data);
			destroy_mtx(&data);
			free_memory(&data);
		}
		else
			return (2);
	}
	else
		return (1);
	return (0);
}
