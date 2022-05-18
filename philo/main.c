#include "philo.h"

void	solitary_philo(t_philos *p, struct timeval tv)
{
	access_last_eat(&p[0], WRITE, tv.tv_sec * 1000 + tv.tv_usec / 1000);
	pthread_create(&p[0].thread, NULL, &philo_routine_solitude, &p[0]);
	pthread_join(p[0].thread, NULL);
}

void	start_thread(t_life *life)
{
	struct timeval	tv;
	t_philos		*p;
	unsigned int	i;

	i = 0;
	p = life->philos;
	gettimeofday(&tv, NULL);
	if (life->pnum == 1)
		return (solitary_philo(p, tv));
	while (i < life->pnum)
	{
		access_last_eat(&p[i], WRITE, tv.tv_sec * 1000 + tv.tv_usec / 1000);
		pthread_create(&p[i].thread, NULL, &philo_routine, &p[i]);
		pthread_create(&p[i].monitor, NULL, &stomach_monitor, &p[i]);
		i++;
	}
	i = 0;
	while (i < life->pnum)
	{
		pthread_join(p[i].monitor, NULL);
		pthread_join(p[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_life	life;

	if (!validate_arg(ac, av))
		return (0);
	if (!init_life(&life, ac, av))
		return (0);
	if (!init_philos(&life))
		return (0);
	init_mutex(&life);
	start_thread(&life);
	if (life.philos)
		free(life.philos);
	if (life.forks)
		free(life.forks);
	return (0);
}
