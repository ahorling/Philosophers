/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/12 20:25:50 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "init_philos.h"
#include "paramedic.h"
#include "philo_utils.h"
#include "structs.h"

// static void	run_thread(t_philo *philo, t_info *info)
// {
// 	usleep (50);
// 	while (1)
// 	{
// 		pthread_mutex_lock(info->printable);
// 		if (check_philos(info, philo) != 0)
// 		{
// 			pthread_mutex_unlock(philo->info->death);
// 			pthread_mutex_unlock(philo->info->printable);
// 			return ;
// 		}
// 		if (info->deadphilo == true)
// 		{
// 			pthread_mutex_unlock(info->death);
// 			pthread_mutex_unlock(info->printable);
// 			return ;
// 		}
// 		printf("%zu: Philosopher number %d says hello!\n", runtime(info), philo->number);
// 		pthread_mutex_unlock(info->printable);
// 	}
// 	return ;
// }

static void	run_thread(t_philo *philo, t_info *info)
{
	usleep (50);
	while (1)
	{
		if (info->num_of_philos == 1)
		{
			
		}
	}
	return ;
}

/*This is the function the threads will run, split off from run_thread to
make the passing of arguments simpler.*/
void *thread_start(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	run_thread(philo, philo->info);
	return (NULL);
}

/*activate the mutex locks on each philosopher, so we can lock
other philosophers from using them later on.*/
int	lock_forks(t_info *info, t_philo *philo)
{
	int		count;

	count = 1;
	if (pthread_mutex_init(philo->info->death, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(philo->info->printable, NULL) != 0)
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
		error = pthread_create(&threads[i], NULL, &thread_start, (void *)temp);
		if (error != 0)
		{
			info->deadphilo = true;
			pthread_mutex_lock(info->death);
			write(STDERR_FILENO, "Thread creation failed\n", 23);
			join_threads(threads, i - 1);
			return (-1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
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
		free_philos(info, philo);
	if (paramedic(info, philo, threads) != 0)
		return (-1);
	join_threads(threads, info->num_of_philos);
	printf("all philos ended\n");
	return (0);
}
