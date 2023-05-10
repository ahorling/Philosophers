/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philos.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:03:01 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/10 23:39:13 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include "include/structs.h"
#include "include/philo_utils.h"

void	*test()
{
	printf("%ld: philo said hello\n", timecall());
	return (0);
}

int	philosophize(t_info *info)
{
	pthread_t thread;

	if (pthread_create(&thread, NULL, &test, NULL) == -1)
		return (1);
	if (pthread_join(thread, NULL) == -1)
		return (1);
	return (0);
}
