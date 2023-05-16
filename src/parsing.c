/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:58 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 22:05:42 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_atoi.h"
#include "ft_strncmp.h"
#include "init_philos.h"
#include "philo_utils.h"
#include "structs.h"

/*check for possible errors in the dictated parameters.*/
int	check_params(t_info *info, int argc, char **argv)
{
	int	i;

	i = 0;
	if (info->num_of_philos < 0)
		i = 2;
	if (info->time_to_die <= 0)
		i = 1;
	if (info->time_to_eat <= 0)
		i = 1;
	if (info->time_to_sleep <= 0)
		i = 1;
	if (info->eat_count <= 0 && argc == 6)
		i = 3;
	if (info->num_of_philos == 0)
		i = 2;
	if (ft_strncmp("above 0", argv[5], 7) == 0)
	{
		write(STDERR_FILENO, "Listen here you little shit...\n", 31);
		return (4);
	}
	return (i);
}

/*return different errors depending on what parsing error was discovered.*/
int	param_errors(t_info *info, int argc, char **argv)
{
	int	error;

	error = check_params(info, argc, argv);
	if (error == 1)
	{
		write(STDERR_FILENO, "invalid time_to_x input\n", 24);
		free(info);
		return (1);
	}
	else if (error == 2)
	{
		write(STDERR_FILENO, "must have at least 1 philosopher, ", 35);
		write(STDERR_FILENO, "or 2 if you don't want it to die alone\n", 39);
		free(info);
		return (1);
	}
	else if (error == 3)
	{
		write(STDERR_FILENO, "if specified, eat_count must above 0\n", 37);
		return (1);
	}
	else if (error == 4)
		return (1);
	return (0);
}

/*Take the dictated paramaters and set up the info struct using that
information as well as some other bits of information such as the start time.*/
t_info	*initialize_info(int argc, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->eat_count = ft_atoi(argv[5]);
	else
		info->eat_count = 0;
	info->starttime = timecall();
	info->deadphilo = false;
	info->finished = false;
	info->death = malloc(sizeof(pthread_mutex_t));
	info->printable = malloc(sizeof(pthread_mutex_t));
	info->timelock = malloc(sizeof(pthread_mutex_t));
	return (info);
}
