/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/11 08:36:08 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "philos.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_info	*info;
	int		error;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	info = initialize_info(info, argc, argv);
	if (!info)
	{
		free(info);
		return (-1);
	}
	if (argc == 6 && info->eat_count == 0)
	{
		free(info);
		return (0);
	}
	error = param_errors(info);
	if (error != 0)
	{
		free(info);
		return (-1);
	}
	philosophize(info);
	free(info);
	return (0);
}