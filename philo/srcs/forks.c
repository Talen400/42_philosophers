/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:08:46 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/08 20:07:11 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * philo takes fork N and N + 1
 *
 * to last philo taken N and 1 fork
 */

int	take_forks(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&first->mutex);
	/*
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&first->mutex);
		return (FAILURE);
	}
	*/
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&second->mutex);
	/*
	if (should_stop(philo))
	{
		pthread_mutex_unlock(&first->mutex);
		pthread_mutex_unlock(&second->mutex);
		return (FAILURE);
	}
	*/
	print_status(philo, "has taken a fork");
	return (SUCESS);
}

/*
 * drop the forks :>
 */

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
