/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:19:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/05 00:14:52 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

typedef struct s_data
{
	long int			num;
	pthread_mutex_t	lock;
}	t_data;

void	*ft_wait(void *arg)
{
	t_data	*shared_data;

	shared_data = (t_data *) arg;
	pthread_mutex_lock(&shared_data->lock);
	while (shared_data->num < 100)
	{
		shared_data->num++;
		printf("%ld\n", shared_data->num);
	}
	printf("Done: %ld\n", shared_data->num);
	pthread_mutex_unlock(&shared_data->lock);
	(void ) arg;
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;
	int			err;
	t_data		data;

	if (argc != 2)
	{
		printf("Error\n");
		return (FAIL);
	}
	if (pthread_mutex_init(&data.lock, NULL) != 0)
	{
		printf("Mudex init failed. \n");
	}
	data.num= 0;
	err = pthread_create(&t1, NULL, ft_wait, &data);
	err += pthread_create(&t2, NULL, ft_wait, &data);
	if (err != 0)
	{
		printf("An error ocurred: %d\n", err);
		return (FAIL);
	}
	printf("Waiting for thread to end...\n");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Thread ended.\n");
	(void ) argc;
	(void ) argv;
	return (SUCESS);
}
