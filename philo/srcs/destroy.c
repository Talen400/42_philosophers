/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:24:19 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/13 00:52:27 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * Free functions
 */

void	destroy_forks(t_data *data)
{
	size_t	i;

	if (!data->forks)
		return ;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
}

static void	destroy_philos(t_philo *philos)
{
	if (philos)
		free(philos);
}

void	destroy_all(t_data *data, t_philo *philos)
{
	destroy_forks(data);
	destroy_mutexes(data);
	destroy_philos(philos);
}
