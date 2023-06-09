/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:23:00 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 21:59:43 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"

int		check_params(t_info *info, int argc, char **argv);
int		param_errors(t_info *info, int argc, char **argv);
t_info	*initialize_info(int argc, char **argv);

#endif