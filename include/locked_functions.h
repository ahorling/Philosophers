/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   locked_functions.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:10:27 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/12 20:11:38 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCKED_FUNCTIONS_H
# define LOCKED_FUNCTIONS_H

# include "structs.h"

int		check_philos(t_info *info, t_philo *philo);
void	print_message(t_info *info, t_philo *philo, char *string);

#endif
