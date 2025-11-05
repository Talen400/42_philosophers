/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:19:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/04 21:05:33 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_wait(void *arg)
{
	int	num;
	int	result;

	num = *(int *) arg;
	result = 1;
	while (num)
	{
		result *= num;
		num--;
	}
	printf("Done: %d\n", result);
	(void ) arg;
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	thread;
	pthread_t	thread2;
	int			err;
	int			num1;
	int			num2;

	if (argc != 2)
	{
		printf("Error\n");
		return (FAIL);
	}
	num1 = ft_atoi(argv[1]);
	err = pthread_create(&thread, NULL, ft_wait, &num1);
	num2 = num1 - 1;
	err += pthread_create(&thread2, NULL, ft_wait, &num2);
	if (err != 0)
	{
		printf("An error ocurred: %d\n", err);
		return (FAIL);
	}
	printf("Waiting for thread to end...\n");
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	printf("Thread ended.\n");
	(void ) argc;
	(void ) argv;
	return (SUCESS);
}
