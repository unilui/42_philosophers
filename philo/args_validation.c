/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 01:58:39 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/05 02:32:48 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	helper(int argc)
{
	if (argc < 2)
		printf("Missing: <number_of_philosopher>\n");
	if (argc < 3)
		printf("Missing: <time_to_die>\n");
	if (argc < 4)
		printf("Missing: <time_to_eat>\n");
	if (argc < 5)
		printf("Missing: <time_to_sleep>\n");
	if (argc > 6)
		printf("Too many arguments.\n");
	printf("Example: philo 5 800 200 200\n");
}

int	check_numbers(int argc, char **argv)
{
	int	i;
	int	x;

	i = 1;
	while (i < argc)
	{
		x = 0;
		while (argv[i][x])
		{
			if (!ft_isdigit(argv[i][x])
				&& argv[i][x] != '-'
				&& argv[i][x] != '+')
			{
				printf("Numeric arguments required.\n");
				printf("Example: philo 5 800 200 200\n");
				return (0);
			}
			x++;
		}
		i++;
	}
	return (1);
}

int	check_values(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0)
		printf("There must be at least one philosopher.\n");
	if (ft_atoi(argv[2]) < 60)
		printf("Minimum time to <time_to_die>: 60 milliseconds.\n");
	if (ft_atoi(argv[3]) < 60)
		printf("Minimum time to <time_to_eat>: 60 milliseconds.\n");
	if (ft_atoi(argv[4]) < 60)
		printf("Minimum time to <time_to_sleep>: 60 milliseconds.\n");
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		printf("Minimum times a philosopher should try to eat: 1\n");
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60
		|| (argc == 6 && ft_atoi(argv[5]) < 0))
	{
		printf("Example: philo 5 800 200 200\n");
		return (0);
	}
	return (1);
}

int	args_validation(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		helper(argc);
		return (0);
	}
	if (!check_numbers(argc, argv)
		|| !check_values(argc, argv))
		return (0);
	return (1);
}
