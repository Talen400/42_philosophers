/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:36:44 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 21:42:32 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * init semaphores
 */

static int	int_sem_utils(t_data *data)
{
	data->write_lock = sem_open("/philo_write", O_CREAT | O_EXCL, 0644, 1);
	if (data->write_lock == SEM_FAILED)
	{
		destroy_semaphores(data);
		return (FAILURE);
	}
	data->dead_lock = sem_open("/philo_dead", O_CREAT | O_EXCL, 0644, 1);
	if (data->dead_lock == SEM_FAILED)
	{
		destroy_semaphores(data);
		return (FAILURE);
	}
	data->meal_lock = sem_open("/philo_meal", O_CREAT | O_EXCL, 0644, 1);
	if (data->meal_lock == SEM_FAILED)
	{
		destroy_semaphores(data);
		return (FAILURE);
	}
	return (SUCESS);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_dead");
	sem_unlink("/philo_meal");
	data->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			data->n_philo);
	if (data->forks == SEM_FAILED)
		return (FAILURE);
	if (int_sem_utils(data))
		return (FAILURE);
	return (SUCESS);
}
