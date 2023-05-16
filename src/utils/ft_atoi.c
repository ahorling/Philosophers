/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:23:39 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/16 20:57:55 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <stdio.h>

int	error_check(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		printf("%c\n", str[i]);
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		return (1);
	return (0);
}

size_t	ft_atoi(const char *str)
{
	size_t	value;
	int		i;
	int		neg;

	i = 0;
	value = 0;
	neg = 1;
	if (error_check(str) != 0)
	{
		write(STDERR_FILENO, "inputs must be numeric\n", 23);	
		return (-1);
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + str[i] - '0';
		i++;
	}
	return (value * neg);
}
