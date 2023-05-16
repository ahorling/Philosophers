/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 02:39:13 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 16:45:12 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PHILOS_H
# define INIT_PHILOS_H

# include "structs.h"

void	free_philos(t_philo *philo);
t_philo	*init_philo(t_info *info, t_philo *philo, int count);
t_philo	*spawn_philos(t_info *info);

#endif