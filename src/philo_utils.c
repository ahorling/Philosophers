/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 21:18:31 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 19:16:53 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include "structs.h"
#include "ft_strlen.h"

/*get the time since january 1st 1970, and convert it into miliseconds.*/
size_t	timecall(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*math out the number of milliseconds since the start of the program*/
size_t	runtime(t_info *info)
{
	size_t	ret;

	ret = timecall() - info->starttime;
	return (ret);
}

/*join the number of threads specified (should be all of them that had been
created up to that point) so that the main process may continue.*/
void	join_threads(pthread_t *threads, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

/*own version of sleep that sleeps in 50 microsecond intervals,
before checking if it no longer needs to sleep anymore.*/
void	good_sleep(t_info *info, size_t sleeptime)
{
	size_t	end;
	size_t	time;

	end = runtime(info) + sleeptime;
	time = runtime(info);
	while (time < end)
	{
		usleep(200);
		time = runtime(info);
	}
}

/*allocate space for all the threads the philosophers are going to use.*/
pthread_t	*spawn_threads(t_info *info)
{
	pthread_t	*threads;

	threads = malloc((info->num_of_philos) * sizeof(pthread_t));
	return (threads);
}
