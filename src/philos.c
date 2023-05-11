/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/11 05:43:49 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "init_philos.h"
#include "philo_utils.h"
#include "structs.h"

void	*run_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sleep(2);
	printf("Philosopher number %d says hello!\n", philo->number);
	return (0);
}

/*activate the mutex lock on each philosopher, so we can lock
other philosophers from using it later on.*/
int	lock_forks(t_info *info, t_philo *philo)
{
	int		count;

	count = 1;
	while (count <= info->num_of_philos)
	{
		if (pthread_mutex_init(philo->fork, NULL) != 0)
			return (-1);
		if (philo->next)
			philo = philo->next;
		count++;
	}
	return (0);
}

/*first activate the mutex lock on the fork each philosopher has, so that
it can be blocked off later. then assign each philosopher it's own thread.*/
int	activate_philos(t_info *info, t_philo *philo, pthread_t *threads)
{
	int 	i;
	int		error;
	t_philo	*temp;

	i = 0;
	temp = philo;
	if (lock_forks(info, philo) != 0)
		return (-1);
	while (i < info->num_of_philos)
	{
		error = pthread_create(&threads[i], NULL, &run_thread, (void *)temp);
		if (error != 0)
		{
			info->isdead = true;
			write(STDERR_FILENO, "Thread creation failed\n", 23);
			join_threads(threads, i - 1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

/*allocate space for all the threads the philosophers are going to use.*/
pthread_t	*spawn_threads(t_info *info)
{
	pthread_t	*threads;

	threads = malloc(info->num_of_philos * sizeof(pthread_t));
	return (threads);
}

/*First set up the philosophers, then create all the threads, assign each philosopher
to their own thread, wait for them to finish one way or another,
and then return back to main process.*/
int	philosophize(t_info *info)
{
	t_philo		*philo;
	pthread_t 	*threads;

	philo = spawn_philos(info);
	if (!philo)
	{
		free(philo);
		return (-1);
	}
	threads = spawn_threads(info);
	if (!threads)
	{
		free(threads);
		return (-1);
	}
	if (activate_philos(info, philo, threads) != 0)
	{
		free_philos(info, philo);
	}
	printf("philos activated\n");
	join_threads(threads, info->num_of_philos);
	printf("all philos ended\n");
	return (0);
}
