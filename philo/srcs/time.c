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

void	wait_until_specified_time(unsigned int time)
{
	long	dest_time;
	long	remain;
	long	t;

	t = (long)time;
	dest_time = get_ustime() + (t * 1000);
	remain = t * 1000;
	while (remain > 0)
	{
		usleep(remain / 2);
		remain = dest_time - get_ustime();
	}
}
