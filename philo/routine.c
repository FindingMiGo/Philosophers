#include "philo.h"

void	*stomach_monitor(void *philo)
{
	t_philos	*p;
	long		time;

	p = philo;
	while (1)
	{
		time = get_mstime();
		if (time >= access_last_eat(p, READ, 0) + p->life->tdie)
		{
			print_act(p, DIE, p->right, true);
			break ;
		}
		usleep(300);
	}
	return (NULL);
}

void	*philo_routine_solitude(void *philo)
{
	t_philos	*p;

	p = philo;
	pthread_mutex_lock(&p->life->forks[0]);
	printf(FMT, get_mstime(), 1, TAKE_MSG);
	wait_for_time(p->life->tdie);
	printf(FMT, get_mstime(), 1, DIE_MSG);
	pthread_mutex_unlock(&p->life->forks[0]);
	return (NULL);
}

void	*philo_routine(void *philo)
{
	t_philos	*p;

	p = philo;
	if ((p->right + 1) % 2 == 0)
		usleep(DELAY);
	while (1)
	{
		philo_take(p);
		philo_eat(p);
		philo_sleep_think(p);
		break ;
	}
	return (NULL);
}