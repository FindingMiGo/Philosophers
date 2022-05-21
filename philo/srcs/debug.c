#include "philo.h"
#include "debug.h"

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
	size_t			i;
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
