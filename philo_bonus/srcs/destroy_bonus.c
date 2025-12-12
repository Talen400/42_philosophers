/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:28:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 21:42:43 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * clean semaphores
 */

void	destroy_semaphores(t_data *data)
{
	if (data->forks)
	{
		sem_close(data->forks);
		sem_unlink("/philo_forks");
	}
	if (data->write_lock)
	{
		sem_close(data->write_lock);
		sem_unlink("/philo_write");
	}
	if (data->dead_lock)
	{
		sem_close(data->dead_lock);
		sem_unlink("/philo_dead");
	}
	if (data->meal_lock)
	{
		sem_close(data->meal_lock);
		sem_unlink("/philo_meal");
	}
}

/*
 * destroy all
 */

void	destroy_all(t_data *data, t_philo *philos)
{
	destroy_semaphores(data);
	if (philos)
		free(philos);
}
