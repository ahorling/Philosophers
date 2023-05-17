/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/17 17:11:41 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "eating.h"
#include "frees.h"
#include "init_philos.h"
#include "locked_functions.h"
#include "paramedic.h"
#include "philo_utils.h"
#include "structs.h"

static void	thread(t_philo *philo, t_info *info)
{
	while (1)
	{
		if (eat(info, philo) != 0)
			return ;
		if (info->finished == true || check_philos(info, philo) != 0)
			return ;
		print_message(info, philo, "is sleeping");
		good_sleep(info, info->time_to_sleep);
		print_message(info, philo, "is thinking");
		if (check_philos(info, philo) != 0)
			return ;
	}
	return ;
}

/*This is the function the threads will run, split off from run_thread to
make the passing of arguments simpler.*/
static void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->number % 2) == 0)
		usleep(philo->info->time_to_eat * 700);
	thread(philo, philo->info);
	return (NULL);
}

/*activate the mutex locks on each philosopher, so we can lock
other philosophers from using them later on.*/
static int	lock_forks(t_info *info, t_philo *philo)
{
	size_t	count;

	count = 1;
	if (pthread_mutex_init(info->death, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(info->printable, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(info->timelock, NULL) != 0)
		return (-1);
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
static int	activate_philos(t_info *info, t_philo *philo, pthread_t *threads)
{
	size_t	i;
	int		error;
	t_philo	*temp;

	i = 0;
	temp = philo;
	if (lock_forks(info, philo) != 0)
		return (-1);
	while (i < info->num_of_philos)
	{
		error = pthread_create(&threads[i], NULL, &thread_start, (void *)temp);
		if (error != 0)
		{
			pthread_mutex_lock(info->death);
			info->deadphilo = true;
			write(STDERR_FILENO, "Thread creation failed\n", 23);
			pthread_mutex_unlock(info->death);
			join_threads(threads, i - 1);
			return (-1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

/*First set up the philosophers, then create all the threads, assign each
philosopher to their own thread, wait for them to finish one way or another,
and then return back to main process.*/
int	philosophize(t_info *info)
{
	t_philo		*philo;
	pthread_t	*threads;
	int			status;

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
		free_philos(philo);
		free_info(info);
		return (-1);
	}
	status = paramedic(info, philo, threads);
	return (free_all(info, philo, threads));
}
