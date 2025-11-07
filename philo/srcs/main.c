/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:19:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/07 00:58:03 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

# define Nt 15
# define MAX 10

typedef struct s_data
{
	int					id;
	long int			num;
}	t_data;

void	*ft_wait(void *arg)
{
	t_data	*data;
	
	data = (t_data *) arg;
	while (data->num < MAX)
	{
		usleep(100*1000);
		printf("Thread %d in %ld\n", data->id, data->num);
		data->num++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	threads[Nt];
	t_data		data[Nt];
	int			err;
	int			i;

	if (argc !=  1)
	{
		printf("Error\n");
		return (FAIL);
	}
	err = 0;
	i = -1;
	while (++i < Nt)
	{
		data[i].id = i;
		data[i].num = 0;
		err += pthread_create(&threads[i], NULL, ft_wait, &data[i]);
		if (err != 0)
		{
			printf("Error failed thread creation\n");
			return (FAIL);
		}
	}
	printf("Waiting for thread to end...\n");
	i = -1;
	while (++i < Nt)
		pthread_join(threads[i], NULL);
	printf("Thread ended.\n");
	(void ) argc;
	(void ) argv;
	return (SUCESS);
}
