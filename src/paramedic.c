/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paramedic.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 12:50:21 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/12 20:15:27 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "locked_functions.h"
#include "philo_utils.h"
#include "structs.h"

#include <stdio.h>

/*constantly checks all the philosophers to make sure none of them have died.
If a dead philo is found, sets the deadphilo bool to true and joins threads*/
int	paramedic(t_info *info, t_philo *philo, pthread_t *threads)
{
	int		status;
	t_philo *temp;

	printf("the paramedic is active\n");
	while (1)
	{
		while (temp)
		{
			status = check_philos(info, temp);
			if (status != 0)
			{
				printf("Philo number %d has died!\n", status);
				info->deadphilo = true;
				pthread_mutex_unlock(info->death);
				join_threads(threads, info->num_of_philos);
				return (-1);
			}
			temp = temp->next;
		}
		temp = philo;
	}
	return (0);
}