/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paramedic.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 12:54:16 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/15 21:29:46 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMEDIC_H
# define PARAMEDIC_H

# include"structs.h"

int	paramedic(t_info *info, t_philo *philo, pthread_t *threads);

#endif