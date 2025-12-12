/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:14:14 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 21:33:49 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
		i++;
	}
	return (philos);
}

/*
 * Initialize all structs
 */

int	init_all(t_data *data, t_philo **philos)
{
	if (init_semaphores(data) != SUCESS)
		return (FAILURE);
	data->start_time = ft_gettime();
	*philos = init_philos(data);
	if (!(*philos))
	{
		destroy_semaphores(data);
		return (FAILURE);
	}
	return (SUCESS);
}
