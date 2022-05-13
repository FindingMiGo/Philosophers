#include "philo.h"

void	print_act(t_philos *p, t_act act, int id)
{
	const char	msg[5][18]
		= {TAKE_MSG, EAT_MSG, SLEEP_MSG, THINK_MSG, DIE_MSG};
	
	pthread_mutex_lock(&p->life->print);
	if (access_end_flag(p->life, READ, false))
	{
		pthread_mutex_unlock(&p->life->print);
		return ;
	}
	if (act == DIE)
		access_end_flag(p->life, WRITE, true);
	printf(FMT, get_mstime(), id, msg[act]);
	pthread_mutex_unlock(&p->life->print);
}

void	philo_sleep_think(t_philos *p)
{
	print_act(p, SLEEP, p->right);
	wait_for_time(p->life->tsleep);
	print_act(p, THINK, p->right);
}

bool	philo_take(t_philos *p)
{
	pthread_mutex_lock(&p->life->forks[p->right]);
	print_act(p, TAKE, p->right);
	pthread_mutex_lock(&p->life->forks[p->left]);
	print_act(p, TAKE, p->right);
	return (true);
}

void	philo_eat(t_philos *p)
{
	p->last_eat = get_mstime();
	print_act(p, EAT, p->right);
	wait_for_time(p->life->teat);
	pthread_mutex_unlock(&p->life->forks[p->right]);
	pthread_mutex_unlock(&p->life->forks[p->left]);
}

void	*stomach_monitor(void *philo)
{
	t_philos	*p;
	long		time;

	p = philo;
	while (access_end_flag(p->life, READ, false) == false)
	{
		time = get_mstime();
		if (time >= p->last_eat + p->life->tdie)
		{
			print_act(p, DIE, p->right);
			break;
		}
		usleep(300);
	}
	return (NULL);
}

void	*philo_routine(void *philo)
{
	t_philos	*p;

	p = philo;
	if ((p->right + 1) % 2 == 0)
		usleep(DELAY);
	pthread_create(&p->monitor, NULL, &stomach_monitor, p);
	while (access_end_flag(p->life, READ, false) == false)
	{
		philo_take(p);
		philo_eat(p);
		philo_sleep_think(p);
	}
	pthread_join(p->monitor, NULL);
	return (NULL);
}

void	start_thread(t_life *life)
{
	struct timeval tv;
	t_philos	*p;
	unsigned int	i;

	i = 0;	
	p = life->philos;
	gettimeofday(&tv, NULL);
	while (i < life->pnum)
	{
		p[i].last_eat = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		pthread_create(&p[i].thread, NULL, &philo_routine, &p[i]);
		i++;
	}
	i = 0;
	while (i < life->pnum)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_life	life;
	
	init_life(&life, ac, av);
	init_philos(&life);
	init_mutex(&life);
	start_thread(&life);
	free(life.philos);
	free(life.forks);
	return (0);
}
