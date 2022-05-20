#include "philo.h"

bool	init_all(t_life *life, int ac, char **av)
{
	if (init_life(life, ac, av) == false)
		return (false);
	if (init_philos(life) == false)
		return (false);
	if (init_mutex(life) == false)
		return (false);
	return (true);
}

void	termination_process(t_life *life)
{
	unsigned int	i;

	i = 0;
	while (i < life->pnum)
	{
		pthread_mutex_destroy(&life->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&life->print);
	pthread_mutex_destroy(&life->last_eat_m);
	pthread_mutex_destroy(&life->completed_m);
	if (life->philos)
		free(life->philos);
	if (life->forks)
		free(life->forks);
}

int	main(int ac, char **av)
{
	t_life	life;

	if (validate_arg(ac, av) == false)
		return (0);
	if (init_all(&life, ac, av) == true)
		start_thread(&life);
	termination_process(&life);
	return (0);
}
