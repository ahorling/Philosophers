
#include <stdio.h>
#include "locked_functions.h"
#include "structs.h"

int	eat(t_info *info, t_philo *philo)
{
	print_message(info, philo, "is eating");
	good_sleep(info->time_to_eat);
	if (starve_check(info, philo) == -1)
		return (-1);
	philo->eat_count++;
	philo->last_ate = runtime(info);
	return (0);
}