/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paramedic.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 12:54:16 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/12 14:53:31 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMEDIC_H
# define PARAMEDIC_H

# include"structs.h"

int	check_philos(t_info *info, t_philo *philo);
int	paramedic(t_info *info, t_philo *philo, pthread_t *threads);

#endif