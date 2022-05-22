#include "philo.h"

bool	print_act(t_philos *p, t_act act, int id, bool end)
{
	bool		ret;
	const char	msg[5][18]
		= {TAKE_MSG, EAT_MSG, SLEEP_MSG, THINK_MSG, DIE_MSG};

	pthread_mutex_lock(&p->life->print);
	ret = true;
	if (access_end_flag(p->life, READ, false) == false)
	{
		printf("%ld %d %s", get_mstime(), id + 1, msg[act]);
		if (end == true)
		{
			access_end_flag(p->life, WRITE, true);
			ret = false;
		}
	}
	else
		ret = false;
	pthread_mutex_unlock(&p->life->print);
	return (ret);
}

bool	philo_sleep_think(t_philos *p)
{
	if (!print_act(p, SLEEP, p->right, false))
		return (false);
	wait_for_specified_time(p->life->tsleep);
	if (!print_act(p, THINK, p->right, false))
		return (false);
	return (true);
}

bool	philo_take(t_philos *p)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&p->life->forks[p->right]);
	if (!print_act(p, TAKE, p->right, false))
		ret = false;
	pthread_mutex_lock(&p->life->forks[p->left]);
	if (!print_act(p, TAKE, p->right, false))
		ret = false;
	if (ret == false)
	{
		pthread_mutex_unlock(&p->life->forks[p->right]);
		pthread_mutex_unlock(&p->life->forks[p->left]);
	}
	return (ret);
}

bool	philo_eat(t_philos *p)
{
	unsigned int	completed;
	bool			ret;

	ret = true;
	access_last_eat(p, WRITE, get_mstime());
	if (!print_act(p, EAT, p->right, false))
		ret = false;
	wait_for_specified_time(p->life->teat);
	if (p->life->eat_limit_f == true)
	{
		p->eat_count++;
		completed = 0;
		if (p->eat_count == p->life->eat_limit)
			completed = access_completed_num(p->life, WRITE);
		if (completed >= p->life->pnum)
			access_end_flag(p->life, WRITE, true);
	}
	pthread_mutex_unlock(&p->life->forks[p->right]);
	pthread_mutex_unlock(&p->life->forks[p->left]);
	return (ret);
}
