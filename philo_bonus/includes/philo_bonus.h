/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:43:07 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 21:43:08 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <time.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# define SUCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

# define MAX_INT 2147483647
# define MIN_INT -2147483648

//# include "semaphore_bonus.h"

/*
 * Global data
 * flags -> someone_died and all_ate_enough
 */

typedef struct s_data
{
	size_t	n_philo;
	long	die;
	long	eat;
	long	sleep;
	long	start_time;
	int		must_eat;
	int		someone_died;
	int		all_ate_enough;
	sem_t	*forks;
	sem_t	*write_lock;
	sem_t	*dead_lock;
	sem_t	*meal_lock;
}	t_data;

/*
 * Philo data
 */

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	long	last_meal_time;
	pid_t	pid;
	t_data	*data;
}	t_philo;

// parse_bonus.c
int		ft_parse(int argc, char **argv, t_data *data);

// ft_handle_bonus.c
int		ft_handler(char *str);

// utils.c
long	ft_gettime(void);
void	ft_usleep(long ms);
void	print_status(t_philo *philo, char *status);
void	print_death(t_philo *philo);
void	*ft_memset(void *s, int c, size_t n);

// init_bonus.c
int		init_all(t_data *data, t_philo **philos);

// destroy_bonus.c
void	destroy_all(t_data *data, t_philo *philos);
void	destroy_semaphores(t_data *data);

// semaphores_bonus.c
int		init_semaphores(t_data *data);

// process_bonus.c
void	philo_process(t_philo *philo);

// monitor_bonus.c
void	*monitor_thread(void *arg);

#endif
