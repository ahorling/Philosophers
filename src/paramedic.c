/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paramedic.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 12:50:21 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 20:33:34 by ahorling      ########   odam.nl         */
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
		printf("%zu %zu %s\n", runtime(info), philo->number, "died");
		pthread_mutex_unlock(info->death);
		return ;
	}
	pthread_mutex_unlock(info->death);
}

/*check if all philos have eaten their fill*/
static int	check_full(int eatcount, t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	pthread_mutex_lock(temp->info->death);
	if (eatcount >= 0)
	{
		while (temp->satiated == true)
		{
			if (temp->next == NULL)
			{
				pthread_mutex_unlock(temp->info->death);
				return (1);
			}
			temp = temp->next;
		}
	}
	pthread_mutex_unlock(temp->info->death);
	return (0);
}

/*once all philos have eaten, set finished to true int the info struct
and print the message that they are done.*/
static void	end_philos(t_info *info, pthread_t *threads)
{
	pthread_mutex_lock(info->death);
	info->finished = true;
	pthread_mutex_unlock(info->death);
	join_threads(threads, info->num_of_philos);
	printf("%zu: All philos have finished eating!\n", runtime(info));
}

/*Set the deadphilo flag to true, print that it died, and
join all the open threads*/
static void	dead_philo(t_info *info, pthread_t *threads, t_philo *temp)
{
	pthread_mutex_lock(info->death);
	info->deadphilo = true;
	pthread_mutex_unlock(info->death);
	print_death(info, temp);
	pthread_mutex_unlock(temp->fork);
	join_threads(threads, info->num_of_philos);
}

/*constantly checks all the philosophers to make sure none of them have died.
If a dead philo is found, sets the deadphilo bool to true and joins threads*/
int	paramedic(t_info *info, t_philo *philo, pthread_t *threads)
{
	int		status;
	t_philo	*temp;

	temp = philo;
	while (1)
	{
		while (temp)
		{
			status = starve_check(info, temp);
			if (status != 0)
			{
				dead_philo(info, threads, temp);
				return (-1);
			}
			temp = temp->next;
		}
		temp = philo;
		if (check_full(info->eat_count, temp) == 1)
		{
			end_philos(info, threads);
			return (1);
		}
	}
	return (0);
}
