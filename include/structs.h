/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:22:52 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/11 05:10:27 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>


/*This struct contains the basic information such as the dictated
parameters, as well as the starttime of the process and
if a philosopher has died.*/
typedef struct	s_info
{
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			eat_count;
	size_t			starttime;
	bool			isdead;
	// t_philo			*firstphilo;
}	t_info;

/*This struct containst all information that each philosopher would need
to do their job, and is linked to the philosopher next in line.*/
typedef struct s_philo
{
	int				number;
	int				eat_count;
	bool			eating;
	size_t			last_ate;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	t_info	*info;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

#endif