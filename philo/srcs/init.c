/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:00:32 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 18:56:48 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * Initialize global mutexes to print and verify dead_lock
 */

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		return (FAILURE);
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->dead_lock);
		return (FAILURE);
	}
	return (SUCESS);
}

/*
 * Initialize array of forks (heap)
 */

static int	init_forks(t_data *data)
{
	size_t	i;

	data->forks = malloc (sizeof(t_fork) * data->n_philo);
	if (!data->forks)
		return (FAILURE);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].mutex);
			free(data->forks);
			return (FAILURE);
		}
		i++;
	}
	return (SUCESS);
}

/*
 * Initialize array of philosofers
 * With ID and circular forks
 */

static t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	size_t	i;

	philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
		i++;
	}
	return (philos);
}

/*
 * Initialize all structs
 */

int	init_all(t_data *data, t_philo **philos)
{
	data->start_time = ft_gettime();
	if (init_mutexes(data))
	{
		destroy_mutexes(data);
		return (FAILURE);
	}
	if (init_forks(data))
	{
		destroy_forks(data);
		destroy_mutexes(data);
		return (FAILURE);
	}
	*philos = init_philos(data);
	if (!philos)
	{
		destroy_all(data, *philos);
		return (FAILURE);
	}
	return (SUCESS);
}
