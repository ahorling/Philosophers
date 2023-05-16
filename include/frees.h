/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frees.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 20:51:27 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 16:39:07 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREES_H
# define FREES_H

# include "structs.h"

void	free_philos(t_philo *philo);
int		free_all(t_info *info, t_philo *philo, pthread_t *threads);

#endif