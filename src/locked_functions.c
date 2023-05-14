/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   locked_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:01:59 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/12 20:25:49 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philo_utils.h"
#include "structs.h"

/*run a check to make sure no philo has died. If a philosopher
has died, return their identifying number.*/
int	check_philos(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(info->death);
	if (philo->isdead == true)
		return (philo->number);
	pthread_mutex_unlock(info->death);
	return (0);
}

/*let the philo print it's message, preventing others from printing their own messages in the meantime*/
void	print_message(t_info *info, t_philo *philo, char *string)
{
	pthread_mutex_lock(info->printable);
	if (philo->isdead == false)
	{
		printf("%zu %d %s\n", runtime(info), philo->number, string);
		pthread_mutex_unlock(info->printable);
		return ;
	}
	pthread_mutex_unlock(info->printable);
}

void	pickup_fork(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	print_message(info, philo, "has taken a fork");
	pthread_mutex_lock(philo->next->fork);
	print_message(info, philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
}

int		starve_check(t_info *info, t_philo *philo)
{
	int time;

	pthread_mutex_lock(info->death);
	time = runtime(info);
	if (time - philo->last_ate >= info->time_to_die)
	{
		philo->isdead = true;
		pthread_mutex_unlock(info->death);
		return (-1);
	}
	pthread_mutex_unlock(info->death);
	return (0);
}