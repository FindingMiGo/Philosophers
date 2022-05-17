#include "philo.h"

bool	is_digit_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_digit_args(int ac, char **av)
{
	size_t	i;

	i = 0;
	while (ac - i > 0)
	{
		if (!is_digit_str(av[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	validate_arg(int ac, char **av)
{
	ac--;
	av++;
	if (!(ac == 4 || ac == 5))
	{
		write(1, "Invalid argument\n", 17);
		return (false);
	}
	if (!is_digit_args(ac, av))
	{
		write(1, "Invalid argument\n", 17);
		return (false);
	}
	return (true);
}

bool	init_life(t_life *life, int ac, char **av)
{
	if (!validate_arg(ac, av))
		return (false);
	ac--;
	av++;
	if (!atoi_philo(&life->pnum, av[0]))
		return (false);
	if (!atoi_philo(&life->tdie, av[1]))
		return (false);
	if (!atoi_philo(&life->teat, av[2]))
		return (false);
	if (!atoi_philo(&life->tsleep, av[3]))
		return (false);
	life->eat_limit = 0;
	if (ac == 5)
	{
		if (!atoi_philo(&life->eat_limit, av[4]))
			return (false);
		life->limit = true;
	}
	life->end = false;
	if (!life->pnum || !life->tdie || !life->teat || !life->tsleep)
	{
		write(1, "Invalid argument\n", 17);
		return (false);
	}
	return (true);
}

bool	init_mutex(t_life *life)
{
	unsigned int	i;

	i = 0;
	life->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * life->pnum);
	if (!life->forks)
	{
		printf("%s\n", "Memory allocation failure");
		return (false);
	}
	if (pthread_mutex_init(&life->print, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&life->flag, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&life->last_eat_m, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&life->completed_m, NULL) != 0)
		return (false);
	while (i < life->pnum)
	{
		if (pthread_mutex_init(&life->forks[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	init_philos(t_life *life)
{
	t_philos		*p;
	unsigned int	i;

	i = 0;
	life->philos = malloc(sizeof(t_philos) * life->pnum);
	if (!life->philos)
	{
		printf("%s\n", "Memory allocation failure");
		return (false);
	}
	p = life->philos;
	while (i < life->pnum)
	{
		p[i].thread = 0;
		p[i].right = i;
		p[i].left = i + 1; 
		p[i].life = life;
		p[i].eat_count = 0;
		i++;
	}
	p[life->pnum - 1].left = 0;
	return (true);
}