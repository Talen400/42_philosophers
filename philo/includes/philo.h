#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>

# define SUCESS 0
# define FAIL 1
# define TRUE 1
# define FALSE 0

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/*
 * Fork data
 */

typedef struct	s_fork
{
	size_t			id;
	pthread_mutex_t	mutex;
}	t_fork;

/*
 * Global data
 */

typedef struct s_data
{
	size_t			n_philo;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	int				must_eat;
	long			start_time;
	int				someone_died;
	t_fork			*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_data;

/*
 * Philo data
 */

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
}	t_philo;

// parse.c
int		ft_parse(int argc, char **argv, t_data *data);

// ft_handle.c
int		ft_handler(char *str);

// utils.c
long	ft_gettime(void);

// destroy.c
void	destrosy_all(t_data *data, t_philo *philos);
#endif
