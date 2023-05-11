/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 21:35:09 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/11 03:29:22 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include <unistd.h>

size_t	timecall();
size_t	runtime(t_info *info);
void	join_threads(pthread_t *threads, int thread_count);

#endif