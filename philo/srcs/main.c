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

int	main(int ac, char **av)
{
	t_life	life;

	if (validate_arg(ac, av) == false)
		return (0);
	if (init_all(&life, ac, av) == true)
	{
		print_life(&life);
		start_thread(&life);
	}
	free_life_and_philos(&life);
	return (0);
}
