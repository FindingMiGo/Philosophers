#include "philo.h"

bool	clear_forks_mutex(t_life *life)
{
	unsigned int	i;

	i = 0;
	while (i < life->pnum)
	{
		pthread_mutex_destroy(&life->forks[i]);
		i++;
	}
	return (true);
}

bool	clear_flag_mutex(t_life *life)
{
	pthread_mutex_destroy(&life->print);
	pthread_mutex_destroy(&life->last_eat_m);
	pthread_mutex_destroy(&life->completed_m);
	return (true);
}

bool	clear_all_mutex(t_life *life)
{
	clear_flag_mutex(life);
	clear_forks_mutex(life);
	return (true);
}

void	free_life_and_philos(t_life *life)
{
	if (life->philos)
		free(life->philos);
	if (life->forks)
		free(life->forks);
}
