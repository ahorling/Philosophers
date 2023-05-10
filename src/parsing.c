/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:58 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/10 23:37:39 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/utils/ft_atoi.h"
#include "include/structs.h"

int	check_params(t_info *info)
{
	int i;

	i = 0;
	if (info->num_of_philos < 0)
		i = 1;
	if (info->time_to_die <= 0)
		i = 1;
	if (info->time_to_eat < 0)
		i = 1;
	if (info->time_to_sleep < 0)
		i = 1;
	if (info->eat_count < 0)
		i = 1;
	if (info->num_of_philos == 0)
		i = 2;
	return (i);
}

int	param_errors(t_info *info)
{
	int error;

	error = check_params(info);
	if (error == 1)
	{
		write(2, "please ensure that your inputs are valid numbers\n", 49);
		free(info);
		return (1);
	}
	if (error == 2)
	{
		write(2, "must have at least 1 philosopher, ", 35);
		write(2, "or 2 if you don't want to watch it die alone\n", 45);
		free(info);
		return (2);
	}
	return (0);
}

t_info	*initialize_params(t_info *info, int argc, char **argv)
{
	t_info	*inf;

	inf = malloc(sizeof(t_info));
	if (!inf)
	{
		//malloc_fail("initialize_params");
		return(NULL);
	}
	inf->num_of_philos = ft_atoi(argv[0]);
	inf->time_to_die = ft_atoi(argv[1]);
	inf->time_to_eat = ft_atoi(argv[2]);
	inf->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		inf->eat_count = ft_atoi(argv[4]);
	else
		inf->eat_count = 0;
	return (inf);
}
