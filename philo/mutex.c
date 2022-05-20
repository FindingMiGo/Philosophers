#include "philo.h"

bool	init_flag_mutex(t_life *life)
{
	if (pthread_mutex_init(&life->print, NULL) != 0)
		return (print_error(INIT_ERR));
	if (pthread_mutex_init(&life->last_eat_m, NULL) != 0)
	{
		pthread_mutex_destroy(&life->print);
		return (print_error(INIT_ERR));
	}
	if (pthread_mutex_init(&life->completed_m, NULL) != 0)
	{
		pthread_mutex_destroy(&life->print);
		pthread_mutex_destroy(&life->last_eat_m);
		return (print_error(INIT_ERR));
	}
	return (true);
}

bool	init_mutex(t_life *life)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	life->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			 * life->pnum);
	ft_memset(life->forks, 0, sizeof(pthread_mutex_t) * life->pnum);
	if (!life->forks)
		return (print_error(MALLOC_ERR));
	if (init_flag_mutex(life) == false)
		return (false);
	while (i < life->pnum)
	{
		if (pthread_mutex_init(&life->forks[i], NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&life->forks[j]);
				j++;
			}
			clear_flag_mutex(life);
			return (print_error(INIT_ERR));
		}
		i++;
	}
	return (true);
}