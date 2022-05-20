#include "philo.h"

bool	solitary_philo(t_philos *p, struct timeval tv)
{
	access_last_eat(&p[0], WRITE, tv.tv_sec * 1000 + tv.tv_usec / 1000);
	if (pthread_create(&p[0].thread, NULL, &philo_routine_solitude, &p[0]) != 0)
		return (print_error(INIT_ERR));
	if (pthread_join(p[0].thread, NULL) != 0)
		return (print_error(INIT_ERR));
	return (true);
}

bool	philo_thread_create(unsigned int pnum, t_philos *p, struct timeval tv)
{
	size_t	i;

	i = 0;
	while (i < pnum)
	{
		access_last_eat(&p[i], WRITE, tv.tv_sec * 1000 + tv.tv_usec / 1000);
		if (pthread_create(&p[i].thread, NULL, &philo_routine, &p[i]) != 0)
			return (print_error(INIT_ERR));
		if (pthread_create(&p[i].monitor, NULL, &stomach_monitor, &p[i]) != 0)
			return (print_error(INIT_ERR));
		i++;
	}
	return (true);
}

bool	philos_thread_join(unsigned int pnum, t_philos *p)
{
	size_t	i;

	i = 0;
	while (i < pnum)
	{
		if (pthread_join(p[i].monitor, NULL) != 0)
			return (print_error(JOIN_ERR));
		if (pthread_join(p[i].thread, NULL) != 0)
			return (print_error(JOIN_ERR));
		i++;
	}
	return (true);
}

bool	start_thread(t_life *life)
{
	struct timeval	tv;
	t_philos		*p;

	p = life->philos;
	gettimeofday(&tv, NULL);
	if (life->pnum == 1)
		return (solitary_philo(p, tv));
	if (philo_thread_create(life->pnum, p, tv) == false)
		return (false);
	if (philos_thread_join(life->pnum, p) == false)
		return (false);
	return (true);
}
