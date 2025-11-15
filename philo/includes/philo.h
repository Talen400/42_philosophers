/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 02:18:00 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/15 06:41:24 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define FAILURE 1
# define TRUE 1
# define FALSE 0

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/*
 * Fork data
 */

typedef struct s_fork
{
	size_t			id;
	pthread_mutex_t	mutex;
}	t_fork;

/*
 * Global data
 * flags -> someone_died and all_ate_enough
 */

typedef struct s_data
{
	size_t			n_philo;
	long			die;
	long			eat;
	long			sleep;
	long			start_time;
	int				must_eat;
	int				someone_died;
	int				all_ate_enough;
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
void	ft_usleep(long ms);
void	print_status(t_philo *philo, char *status);
void	print_death(t_philo *philo);

// init.c
int		init_all(t_data *data, t_philo **philos);

// destroy.c
void	destroy_all(t_data *data, t_philo *philos);
void	destroy_forks(t_data *data);
void	destroy_mutexes(t_data *data);

// forks.c
int		take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

// routine.c
void	thinking(t_philo *philo);
int		eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	*philo_routine(void *arg);

// monitor.c
void	*monitor_routine(void *arg);
int	should_stop(t_philo *philo);

#endif
