/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahorling <ahorling@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 17:02:51 by ahorling      #+#    #+#                 */
/*   Updated: 2023/05/10 17:23:20 by ahorling      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing.h"
#include "structs.h"

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
			return ;
		error = param_errors(info);
		if (error != 0)
			return ;
		philosophize(info);
	}
	free(info);
	return ;
}