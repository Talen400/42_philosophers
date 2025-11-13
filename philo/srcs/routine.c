/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 01:06:20 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/13 02:17:44 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * function of philo'think :>
 */

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
}

/*
 * function of philo'eat
 */

void	eating(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = ft_gettime();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->eat);
	drop_forks(philo);
}

/*
 * function of philo'sleep
 */

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->sleep);
}

/*
 * Routine of the philo
 */

static int	should_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->dead_lock);
	stop = (philo->data->someone_died || philo->data->all_ate_enough);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (stop);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->n_philo == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!should_stop(philo))
	{
		thinking(philo);
		eating(philo);
		if (should_stop(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}
