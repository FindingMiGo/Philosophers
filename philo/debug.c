#include "philo.h"
#include "debug.h"

long	get_mstime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec *1000 + tv.tv_usec / 1000);
}

long	get_ustime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	wait_for_time(long int time)
{
	const long	dest_time = time * 1000 + get_ustime();
	long	left_time;

	left_time = time * 1000;
	while (left_time > 0)
	{
		usleep(left_time / 2);
		left_time = dest_time - get_ustime();
	}
}

void	print_life(t_life *life)
{
	if (!life)
		return ;
	printf("philos\t\t: %d\n", life->pnum);
	printf("die time\t: %d\n", life->tdie);
	printf("eat time\t: %d\n", life->teat);
	printf("sleep time\t: %d\n", life->tsleep);
	printf("eat limit\t: %d\n", life->eat_limit);
}

void	print_philos(t_philos *p)
{
	size_t	i;
	unsigned int	pnum;

	if (!p)
		return ;
	i = 0;
	pnum = p[0].life->pnum;
	while (i < pnum)
	{
		printf("-----\n");
		printf("right\t\t: %d\n", p[i].right);
		printf("left\t\t: %d\n", p[i].left);
		printf("last eat\t: %ld\n", p[0].last_eat);
		printf("life\t\t: %p\n", p[0].life);
		i++;
	}
}