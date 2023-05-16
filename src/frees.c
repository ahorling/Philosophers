/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frees.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 20:46:14 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 20:09:43 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "structs.h"

/*Destroy and then free all the mutexs in info*/
void	free_info(t_info *info)
{
	if (info->death)
	{
		pthread_mutex_destroy(info->death);
		free(info->death);
	}
	if (info->printable)
	{
		pthread_mutex_destroy(info->printable);
		free(info->printable);
	}
	if (info->timelock)
	{
		pthread_mutex_destroy(info->timelock);
		free(info->timelock);
	}
	free(info);
}

void	free_threads(pthread_t *threads)
{
	free(threads);
}

/*loop through the list of philosophers starting at the and free as you go.*/
void	free_philos(t_philo *philo)
{
	t_philo	*temp;

	if (!philo)
		return ;
	while (philo->prev)
		philo = philo->prev;
	while (philo)
	{
		temp = philo->next;
		if (philo->fork)
		{
			pthread_mutex_destroy(philo->fork);
			free(philo->fork);
		}
		free(philo);
		philo = temp;
	}
}

/*go through all the things that have been set, and free em*/
int	free_all(t_info *info, t_philo *philo, pthread_t *threads)
{
	free_philos(philo);
	free_threads(threads);
	free_info(info);
	return (0);
}
