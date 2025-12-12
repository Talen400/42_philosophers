/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:38:40 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 21:38:45 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitor_thread(void *arg)
{
	t_philo	*philo;
	long	time_since_meal;

	philo = (t_philo *) arg;
	while (TRUE)
	{
		usleep(1000);
		sem_wait(philo->data->meal_lock);
		time_since_meal = ft_gettime() - philo->last_meal_time;
		sem_post(philo->data->meal_lock);
		if (time_since_meal > philo->data->die)
		{
			print_death(philo);
			exit(1);
		}
	}
	return (NULL);
}
