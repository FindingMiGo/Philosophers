#ifndef  PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include "struct.h"
# include "debug.h"

# define FMT "%ld %d %s"
# define TAKE_MSG "has taken a fork\n"
# define EAT_MSG "is eating\n"
# define SLEEP_MSG "is sleeping\n"
# define THINK_MSG "is thinking\n"
# define DIE_MSG "is died\n"

# ifndef DELAY
# 	define DELAY 100
# endif

typedef enum e_act{
	TAKE,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_act;

typedef enum e_rw{
	READ,
	WRITE
}	t_rw;

int	ft_isdigit(int c);
bool	atoi_philo(unsigned int *num, const char *str);
bool	atol_philo(unsigned long *num, const char *str);

bool	validate_arg(int ac, char **av);
bool	init_life(t_life *life, int ac, char **av);
bool	init_mutex(t_life *life);
bool	init_philos(t_life *life);
bool	access_end_flag(t_life *life, t_rw rw, bool on);

#endif