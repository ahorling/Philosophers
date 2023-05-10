/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/10 23:45:29 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "include/parsing.h"
#include "include/parsing.h"
#include "include/philos.h"

int	main(int argc, char **argv)
{
	t_info	*info;
	int		error;

	if (argc != 4 || argc != 5)
		printf("Invalid number of arguments\n");
	else
	{
		*info = initialize_params(info, argc, argv);
		if (!info)
			return (1);
		error = param_errors(info);
		if (error != 0)
			return (1);
		philosophize(info);
		free(info);
	}
	return (0);
}