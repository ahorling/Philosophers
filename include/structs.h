
#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>

typedef struct	s_info
{
	size_t		num_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		eat_count;
}	t_info;

#endif