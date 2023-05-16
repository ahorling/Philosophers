/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   locked_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:01:59 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 20:29:16 by ahorling      ########   odam.nl         */
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
	t_philo	*temp;

	temp = philo;
	while (temp->prev != NULL)
		temp = temp->prev;
	pthread_mutex_lock(info->death);
	if (info->deadphilo == true)
	{
		pthread_mutex_unlock(info->timelock);
		pthread_mutex_unlock(philo->fork);
		if (philo->number == info->num_of_philos)
			pthread_mutex_unlock(temp->fork);
		else
			pthread_mutex_unlock(philo->next->fork);
		pthread_mutex_unlock(info->death);
		return (philo->number);
	}
	pthread_mutex_unlock(info->death);
	return (0);
}

/*let the philo print it's message, preventing others 
from printing their own messages in the meantime*/
void	print_message(t_info *info, t_philo *philo, char *string)
{
	if (check_philos(info, philo) != 0)
		return ;
	pthread_mutex_lock(info->death);
	pthread_mutex_lock(info->printable);
	if (info->deadphilo == false)
	{
		printf("%zu %zu %s\n", runtime(info), philo->number, string);
		pthread_mutex_unlock(info->printable);
		pthread_mutex_unlock(info->death);
		return ;
	}
	pthread_mutex_unlock(info->printable);
	pthread_mutex_unlock(info->death);
}

/*pickup the forkof philo and philo +1, unless you are the last one
in which case take the fork of philo 1*/
void	pickup_fork(t_info *info, t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	while (temp->prev != NULL)
		temp = temp->prev;
	if (check_philos(info, philo) != 0)
		return ;
	pthread_mutex_lock(philo->fork);
	print_message(info, philo, "has taken a fork");
	if (check_philos(info, philo) != 0)
		return ;
	if (philo->number != info->num_of_philos)
		pthread_mutex_lock(philo->next->fork);
	else
	{
		if (info->num_of_philos == 1)
		{
			good_sleep(info, info->time_to_die);
			return ;
		}
		pthread_mutex_lock(temp->fork);
	}
	if (check_philos(info, philo) != 0)
		return ;
	print_message(info, philo, "has taken a fork");
}

/*drop the two forks the philo is holding*/
void	drop_forks(t_philo *philo)
{
	t_philo	*temp;

	temp = philo;
	while (temp->prev != NULL)
		temp = temp->prev;
	pthread_mutex_unlock(philo->fork);
	if (philo->number != philo->info->num_of_philos)
		pthread_mutex_unlock(philo->next->fork);
	else
		pthread_mutex_unlock(temp->fork);
}

/*loop check the stated philo to see if it is still alive.
temp exists in case the stated philo is the last one, so it can
drop the fork of philo 1 if it has died.*/
int	starve_check(t_info *info, t_philo *philo)
{
	int		time;
	t_philo	*temp;

	temp = philo;
	while (temp->prev != NULL)
		temp = temp->prev;
	pthread_mutex_lock(info->death);
	pthread_mutex_lock(info->timelock);
	time = runtime(info);
	if (time - philo->last_ate >= info->time_to_die)
	{
		philo->isdead = true;
		pthread_mutex_unlock(philo->fork);
		if (philo->number != info->num_of_philos)
			pthread_mutex_unlock(philo->next->fork);
		else
			pthread_mutex_unlock(temp->fork);
		pthread_mutex_unlock(info->timelock);
		pthread_mutex_unlock(info->death);
		return (-1);
	}
	pthread_mutex_unlock(info->timelock);
	pthread_mutex_unlock(info->death);
	return (0);
}
