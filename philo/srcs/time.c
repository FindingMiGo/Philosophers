#include "philo.h"

long	get_mstime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_ustime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	wait_for_specified_time(long int time)
{
	long	dest_time;
	long	left_time;

	dest_time = get_ustime() + time * 1000;
	left_time = time * 1000;
	while (left_time > 0)
	{
		usleep(left_time / 2);
		left_time = dest_time - get_ustime();
	}
}
