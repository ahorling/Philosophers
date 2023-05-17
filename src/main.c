/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/17 17:11:24 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "frees.h"
#include "philos.h"
#include "parsing.h"

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = NULL;
	atexit(leaks);
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	info = initialize_info(argc, argv);
	if (!info)
		return (-1);
	if (!info->death || !info->timelock || !info->printable)
	{
		write(STDERR_FILENO, "Initialization of a mutex lock failed\n", 38);
		free_info(info);
		return (1);
	}
	if (param_errors(info, argc, argv) != 0)
	{
		free_info(info);
		return (-1);
	}
	philosophize(info);
	return (0);
}
