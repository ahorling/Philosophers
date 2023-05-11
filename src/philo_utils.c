/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 21:18:31 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/11 03:55:37 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include "structs.h"

/*get the time since january 1st 1970, and convert it into miliseconds.*/
size_t	timecall()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*math out the number of milliseconds since the start of the program*/
size_t	runtime(t_info *info)
{
	return (timecall() - info->starttime);
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