#include "philo.h"

bool	print_error(t_err msg)
{
	if (msg == ARG_ERR)
		write(2, "Invalid argument\n", 17);
	else if (msg == MALLOC_ERR)
		write(2, "Memory allocation failure\n", 26);
	else if (msg == LARGE_ERR)
		write(2, "The value is too large\n", 23);
	else if (msg == INIT_ERR)
		write(2, "Initialization failure\n", 23);
	else if (msg == JOIN_ERR)
		write(2, "Failure to wait for thread to end\n", 34);
	return (false);
}

bool	validate_arg(int ac, char **av)
{
	ac--;
	av++;
	if (!(ac == 4 || ac == 5))
		return (print_error(ARG_ERR));
	if (!is_digit_args(ac, av))
		return (print_error(ARG_ERR));
	return (true);
}

bool	init_life(t_life *life, int ac, char **av)
{
	ac--;
	av++;
	memset(life, 0, sizeof(t_life));
	if (!atoi_philo(&life->pnum, av[0]))
		return (print_error(LARGE_ERR));
	if (!atoi_philo(&life->tdie, av[1]))
		return (print_error(LARGE_ERR));
	if (!atoi_philo(&life->teat, av[2]))
		return (print_error(LARGE_ERR));
	if (!atoi_philo(&life->tsleep, av[3]))
		return (print_error(LARGE_ERR));
	if (ac == 5)
	{
		if (!atoi_philo(&life->eat_limit, av[4]))
			return (print_error(LARGE_ERR));
		if (life->eat_limit == 0)
			return (print_error(ARG_ERR));
		life->eat_limit_f = true;
	}
	if (!life->pnum || !life->tdie || !life->teat || !life->tsleep)
		return (print_error(ARG_ERR));
	return (true);
}

bool	init_philos(t_life *life)
{
	t_philos		*p;
	unsigned int	i;

	i = 0;
	life->philos = malloc(sizeof(t_philos) * life->pnum);
	if (!life->philos)
		return (print_error(MALLOC_ERR));
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
