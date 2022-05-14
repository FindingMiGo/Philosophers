#include "philo.h"

bool	access_end_flag(t_life *life, t_rw rw, bool on)
{
	bool ret;

	pthread_mutex_lock(&life->flag);
	ret = false;
	if (rw == WRITE)
		life->end = on;
	else
		ret = life->end;
	pthread_mutex_unlock(&life->flag);
	return (ret);
}

long	access_last_eat(t_philos *philo, t_rw rw, long time)
{
	long ret;

	ret = 0;
	pthread_mutex_lock(&philo->life->last_eat_m);
	if (rw == WRITE)
		philo->last_eat = time;
	else
		ret = philo->last_eat;
	pthread_mutex_unlock(&philo->life->last_eat_m);
	return (ret);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

bool	atoi_philo(unsigned int *num, const char *str)
{
	long long	ans;
	size_t		i;

	i = 0;
	ans = 0;
	*num = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (ans > (INT_MAX - (str[i] - '0')) / 10)
			return (false);
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	*num = ans;
	return (true);
}

bool	atol_philo(unsigned long *num, const char *str)
{
	long long	ans;
	size_t		i;

	i = 0;
	ans = 0;
	*num = 0;
	while (ft_isdigit(str[i]))
	{
		if (ans > (LONG_MAX - (str[i] - '0')) / 10)
			return (false);
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	*num = ans;
	return (true);
}
