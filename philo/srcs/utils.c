/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:49:58 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/13 01:37:48 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * get time of the UNIX system
 */

long	ft_gettime(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

/*
 * usleep() is very speed and imprecision.
 *
 * And it might accumulate a few 1ms
 * and accidentally kill some philosopher.
 *
 * So, this function pause 0.5ms to calculate time :>
 */

void	ft_usleep(long ms)
{
	long	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < ms)
		usleep(500);
}

/*
 * To threads not try write the some buffer in same time
 * This protect the buffer with mutex
 */
void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = ft_gettime() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->write_lock);
}
