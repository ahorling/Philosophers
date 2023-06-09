/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:59 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 22:37:16 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "locked_functions.h"
#include "philo_utils.h"
#include "structs.h"

/*Pick up the forks, then wait for the eating time dictated,
then increment the eat count and drop the forks*/
int	eat(t_info *info, t_philo *philo)
{
	if (check_philos(info, philo) != 0)
		return (1);
	pickup_fork(info, philo);
	print_message(info, philo, "is eating");
	good_sleep(info, info->time_to_eat);
	if (check_philos(info, philo) != 0)
		return (1);
	philo->eat_count++;
	pthread_mutex_lock(info->death);
	if (philo->eat_count == info->eat_count)
		philo->satiated = true;
	pthread_mutex_unlock(info->death);
	pthread_mutex_lock(info->timelock);
	philo->last_ate = runtime(info);
	pthread_mutex_unlock(info->timelock);
	drop_forks(philo);
	if (check_philos(info, philo) != 0)
		return (1);
	return (0);
}
