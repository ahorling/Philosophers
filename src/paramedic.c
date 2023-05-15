/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paramedic.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 12:50:21 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/15 22:14:55 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "locked_functions.h"
#include "philo_utils.h"
#include "structs.h"

#include <stdio.h>

/*if paramedic detects that someone died, print that.*/
void	print_death(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(info->death);
	if (philo->isdead == true)
	{
		printf("%zu %d %s\n", runtime(info), philo->number, "died");
		pthread_mutex_unlock(info->death);
		return ;
	}
	pthread_mutex_unlock(info->death);
}

/*check if all philos have eaten their fill*/
static int	check_full(int eatcount, t_philo *philo)
{
	t_philo *temp;

	temp = philo;
	if (eatcount >= 0)
	{
		while(temp->satiated == true)
		{
			if(temp->next == NULL)
				return (1);
			temp = temp->next;
		}
	}
	return (0);
}

/*constantly checks all the philosophers to make sure none of them have died.
If a dead philo is found, sets the deadphilo bool to true and joins threads*/
int	paramedic(t_info *info, t_philo *philo, pthread_t *threads)
{
	int		status;
	t_philo *temp;

	while (1)
	{
		while (temp)
		{
			status = starve_check(info, temp);
			if (status != 0)
			{
				info->deadphilo = true;
				print_death(info, temp);
				join_threads(threads, info->num_of_philos);
				return (-1);
			}
			temp = temp->next;
		}
		temp = philo;
		if (check_full(info->eat_count, temp) == 1)
		{
			info->finished = true;
			join_threads(threads, info->num_of_philos);
			printf("%zu: All philos have finished eating!\n", runtime(info));
			return (1);
		}
	}
	return (0);
}