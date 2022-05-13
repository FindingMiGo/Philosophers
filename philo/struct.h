#ifndef  STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_philos{
	pthread_t	thread;
	pthread_t	monitor;
	int			right;
	int			left;
	long		last_eat;
	struct s_life	*life;
}	t_philos;

typedef struct s_life{
	unsigned int	pnum;
	unsigned int	tdie;
	unsigned int	teat;
	unsigned int	tsleep;
	unsigned int	eat_limit;
	bool			end;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	flag;
	}	t_life;

#endif