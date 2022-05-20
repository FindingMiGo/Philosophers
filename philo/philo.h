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

# define FMT "%ld %3d %s"
# define TAKE_MSG "has taken a fork\n"
# define EAT_MSG "is eating\n"
# define SLEEP_MSG "is sleeping\n"
# define THINK_MSG "is thinking\n"
# define DIE_MSG "is died\n"

# ifndef DELAY
#  define DELAY 300
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

typedef enum e_err{
	ARG_ERR,
	MALLOC_ERR,
	OF_ERR,
	INIT_ERR,
	JOIN_ERR
}	t_err;

int				ft_isdigit(int c);
bool			atoi_philo(unsigned int *num, const char *str);
bool			atol_philo(unsigned long *num, const char *str);

bool			validate_arg(int ac, char **av);
bool			init_life(t_life *life, int ac, char **av);
bool			init_mutex(t_life *life);
bool			init_philos(t_life *life);
bool			access_end_flag(t_life *life, t_rw rw, bool on);
long			access_last_eat(t_philos *philo, t_rw rw, long time);
unsigned int	access_completed_num(t_life *life, t_rw rw);

bool			is_digit_args(int ac, char **av);

bool			print_act(t_philos *p, t_act act, int id, bool end);
bool			philo_take(t_philos *p);
bool			philo_eat(t_philos *p);
bool			philo_sleep_think(t_philos *p);

void			*stomach_monitor(void *philo);
void			*philo_routine_solitude(void *philo);
void			*philo_routine(void *philo);

bool			start_thread(t_life *life);
void			*ft_memset(void *b, int c, size_t len);

bool	print_error(t_err msg);

bool	clear_flag_mutex(t_life *life);
bool	clear_all_mutex(t_life *life);
void	free_life_and_philos(t_life *life);
#endif