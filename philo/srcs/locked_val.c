#include "philo.h"

long	access_last_eat(t_philos *philo, t_rw rw, long time)
{
	long	ret;

	pthread_mutex_lock(&philo->life->last_eat_m);
	ret = 0;
	if (rw == WRITE)
		philo->last_eat = time;
	else
		ret = philo->last_eat;
	pthread_mutex_unlock(&philo->life->last_eat_m);
	return (ret);
}

unsigned int	access_completed_num(t_life *life, t_rw rw)
{
	unsigned int	ret;

	pthread_mutex_lock(&life->completed_m);
	ret = 0;
	if (rw == WRITE)
	{
		life->completed_c++;
		ret = life->completed_c;
	}
	else
		ret = life->completed_c;
	pthread_mutex_unlock(&life->completed_m);
	return (ret);
}
