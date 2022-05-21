#ifndef  DEBUG_H
# define DEBUG_H

# include "struct.h"
# include "philo.h"

void	print_life(t_life *life);
void	print_philos(t_philos *p);
long	get_mstime(void);
void	wait_for_specified_time(long int time);

#endif