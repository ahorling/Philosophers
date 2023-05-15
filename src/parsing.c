/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:58 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/15 22:17:36 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "init_philos.h"
#include "ft_atoi.h"
#include "structs.h"
#include "philo_utils.h"

/*check for possible errors in the dictated parameters.*/
int	check_params(t_info *info, int argc)
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
	if (info->eat_count < 0 && argc == 6)
		i = 1;
	if (info->num_of_philos == 0)
		i = 2;
	if (info->num_of_philos > 1000)
		i = 3;
	return (i);
}

/*return different errors depending on what parsing error was discovered.*/
int	param_errors(t_info *info, int argc)
{
	int error;

	error = check_params(info, argc);
	if (error == 1)
	{
		write(STDERR_FILENO, "please ensure that your inputs are valid numbers\n", 49);
		free(info);
		return (1);
	}
	else if (error == 2)
	{
		write(STDERR_FILENO, "must have at least 1 philosopher, ", 35);
		write(STDERR_FILENO, "or 2 if you don't want to watch it die alone\n", 45);
		free(info);
		return (1);
	}
	else if (error == 3)
	{
		write(STDERR_FILENO, "That is way too many philosophers buddy ", 41);
		write(STDERR_FILENO, "please choose a smaller number\n", 31);
		free(info);
		return (1);
	}
	return (0);
}

/*Take the dictated paramaters and set up the information struct using that information,
as well as some other bits of information such as the start time.*/
t_info	*initialize_info(t_info *info, int argc, char **argv)
{
	t_info	*inf;

	inf = malloc(sizeof(t_info));
	if (!inf)
		return (NULL);
	inf->num_of_philos = ft_atoi(argv[1]);
	inf->time_to_die = ft_atoi(argv[2]);
	inf->time_to_eat = ft_atoi(argv[3]);
	inf->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		inf->eat_count = ft_atoi(argv[5]);
	else
		inf->eat_count = -1;
	// printf("number of philosophers is: %zu\n", inf->num_of_philos);
	// printf("time before a philosopher dies is: %zu\n", inf->time_to_die);
	// printf("times a philosopher must eat is: %zu\n", inf->time_to_eat);
	// printf("times a philosopher must sleep is: %zu\n",inf->time_to_sleep);
	// printf("amount of times a philosopher must eat is: %zu\n", inf->eat_count);
	inf->starttime = timecall();
	inf->deadphilo = false;
	inf->finished = false;
	inf->death = malloc(sizeof(pthread_mutex_t));
	inf->printable = malloc(sizeof(pthread_mutex_t));
	inf->timelock = malloc(sizeof(pthread_mutex_t));
	return (inf);
}
