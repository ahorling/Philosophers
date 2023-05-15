/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 01:14:07 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/15 20:52:21 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include "frees.h"
#include "structs.h"



#include <stdio.h>

/*initialize each philosopher as it is added to the linked list of philosophers*/
t_philo	*init_philo(t_info *info, t_philo *philo, int count)
{
	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		free_philos(info, philo);
		return (NULL);
	}
	philo->number = count;
	philo->eat_count = 0;
	philo->last_ate = 0;
	philo->isdead = false;
	philo->satiated = false;
	philo->fork = malloc(sizeof(pthread_mutex_t));
	if (!philo->fork)
	{
		free_philos(info, philo);
		return (NULL);
	}
	philo->info = info;
	philo->next = NULL;
	return(philo);
}

/*Begin spawning philosophers by setting them in a soubly linked list*/
t_philo	*spawn_philos(t_info *info)
{
	int		count;
	t_philo	*philo;

	count = 1;
	philo = init_philo(info, philo, count);
	if (!philo)
		return (NULL);
	philo->prev = NULL;
	count++;
	while (count <= info->num_of_philos)
	{
		philo->next = init_philo(info, philo, count);
		philo->next->prev = philo;
		philo = philo->next;
		count++;
	}
	while (philo->prev)
		philo = philo->prev;
	return (philo);
}
