/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 21:59:20 by ahorling      ########   odam.nl         */
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

	info = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	info = initialize_info(argc, argv);
	if (!info)
	{
		free(info);
		return (-1);
	}
	error = param_errors(info, argc, argv);
	if (error != 0)
		return (-1);
	philosophize(info);
	return (0);
}
