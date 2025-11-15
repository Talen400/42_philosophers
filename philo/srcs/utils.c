/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:49:58 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/15 07:11:38 by tlavared         ###   ########.fr       */
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
	long	elapsed;
	long	remaining;

	start = ft_gettime();
	while (1)
	{
		elapsed = ft_gettime() - start;
		remaining = ms - elapsed;
		if (remaining <= 0)
			break ;
		else if (remaining > 1)
			usleep(100);
		else
			usleep(10);
	}
}

/*
 * To threads not try write the some buffer in same time
 * This protect the buffer with mutex
 *
 * And print only philo while lives
 */

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	int		stop;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	stop = (philo->data->someone_died || philo->data->all_ate_enough);
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (stop == FALSE)
	{
		timestamp = ft_gettime() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

/*
 * print when a philo died
 */

void	print_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	timestamp = ft_gettime() - philo->data->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}
