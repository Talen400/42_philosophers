/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 05:20:29 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 20:54:04 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * The monitor have two functions:
 * - check someone is died
 * - check if all eated enough
 * check in 1 ms
 *
 */

static int	check_death(t_philo *philos)
{
	size_t	i;
	long	last_meal;
	long	time_since_meal;
	t_data	*data;

	data = philos[0].data;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		last_meal = philos[i].last_meal_time;
		pthread_mutex_unlock(&data->meal_lock);
		time_since_meal = ft_gettime() - last_meal;
		if (time_since_meal > data->die)
		{
			print_death(&philos[i]);
			pthread_mutex_lock(&data->dead_lock);
			data->someone_died = TRUE;
			pthread_mutex_unlock(&data->dead_lock);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static int	check_meals(t_philo *philos)
{
	size_t	i;
	int		all_done;
	t_data	*data;
	int		meals;

	data = philos[0].data;
	if (data->must_eat == -1)
		return (FALSE);
	all_done = TRUE;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		meals = philos[i].meals_eaten;
		pthread_mutex_unlock(&data->meal_lock);
		if (meals <= data->must_eat)
		{
			all_done = FALSE;
			break ;
		}
		i++;
	}
	return (all_done);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *) arg;
	data = philos[0].data;
	while (TRUE)
	{
		if (check_death(philos))
			return (NULL);
		if (check_meals(philos))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->all_ate_enough = TRUE;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
