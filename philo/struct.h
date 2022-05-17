#ifndef  STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_philos{
	pthread_t		thread;
	pthread_t		monitor;
	int				right;
	int				left;
	long			last_eat;
	unsigned int	eat_count;
	struct s_life	*life;
}	t_philos;

typedef struct s_life{
	unsigned int	pnum;
	unsigned int	tdie;
	unsigned int	teat;
	unsigned int	tsleep;
	unsigned int	eat_limit;
	unsigned int	completed_c;
	bool			end;
	bool			limit;
	t_philos		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	flag;
	pthread_mutex_t	last_eat_m;
	pthread_mutex_t	completed_m;
	}	t_life;

#endif