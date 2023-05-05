#include <unistd.h>
#include "philos_utils.h"
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
		error = check_params(info);
		if (error = 1)
		{
			write(2, "please ensure that your inputs are valid numbers\n", 49);
			free(info);
			return ;
		}
		if (error = 2)
		{
			write(2, "must have at least 1 philosopher, ", 35);
			write(2, "or 2 if you don't want to watch it die alone\n", 45);
			free(info);
			return ;
		}
		philosophize(info);
	}
	free(info);
	return ;
}