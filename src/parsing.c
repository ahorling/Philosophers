/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:58 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/10 17:21:28 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_atoi.h"
#include "structs.h"

int	param_errors(t_info *info)
{
	int error;

	error = check_params(info);
	if (error = 1)
	{
		write(2, "please ensure that your inputs are valid numbers\n", 49);
		free(info);
		return (1);
	}
	if (error = 2)
	{
		write(2, "must have at least 1 philosopher, ", 35);
		write(2, "or 2 if you don't want to watch it die alone\n", 45);
		free(info);
		return (2);
	}
	return (0);
}

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

t_info	*initialize_params(t_info *info, int argc, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
	{
		malloc_fail("initialize_params");
		return(NULL);
	}
	info->num_of_philos = ft_atoi(argv[0]);
	info->time_to_die = ft_atoi(argv[1]);
	info->time_to_eat = ft_atoi(argv[2]);
	info->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		info->eat_count = ft_atoi(argv[4]);
	else
		info->eat_count = 0;
	return (info);
}