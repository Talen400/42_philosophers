/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:42:06 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 21:39:18 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
static int	someone_died(t_philo *philo)
{
	return (FALSE);
}
*/

/*
 * function of philo'think :>
 */

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->data->n_philo % 2 != 0)
		ft_usleep(10);
}

/*
 * function of philo'eat
 */

int	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	sem_wait(philo->data->meal_lock);
	philo->last_meal_time = ft_gettime();
	philo->meals_eaten++;
	sem_post(philo->data->meal_lock);
	ft_usleep(philo->data->eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (SUCESS);
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
 *
 * start with uneven numbers
 * Then, start process
 *
 */

void	philo_process(t_philo *philo)
{
	pthread_t	monitor;

	if (philo->data->n_philo == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->die);
		exit(1);
	}
	pthread_create(&monitor, NULL, monitor_thread, philo);
	pthread_detach(monitor);
	if (philo->id % 2 != 1)
		ft_usleep(1);
	while (TRUE)
	{
		thinking(philo);
		eating(philo);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten > philo->data->must_eat)
			exit(0);
		sleeping(philo);
	}
}
