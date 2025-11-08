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
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_data_time
{
	size_t		n_philo;
	size_t		die;
	size_t		eat;
	size_t		sleep;
	size_t		must_eat;
}	t_data_time;

typedef struct s_forks
{
	pthread_mutex_t	fork_right;
	pthread_mutex_t	fork_left;
}	t_forks;

typedef struct s_philo
{
	pthread_t		id;
	t_data_time		times;
	t_forks			forks;
}	t_philo;

int	ft_atoi(const char *nptr);
int	ft_parse(int argc, char **argv, t_data_time *times);
#endif
