/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:19:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/11 22:37:32 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_main(t_data *data, t_philo **philos)
{
	pthread_t	monitor;
	size_t		i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&(*philos)[i].thread, NULL,
			philo_routine, &(*philos)[i]) != 0)
		{
			destroy_all(data, *philos);
			return (ft_handler("thead creatiion failed\n"));
		}
	}
	pthread_create(&monitor, NULL, monitor_routine, *philos);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_join((*philos)[i].thread, NULL);
	destroy_all(data, *philos);
	return (SUCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	ft_memset(&data, 0, sizeof(t_data));
	philos = ft_memset(&philos, 0, sizeof(t_philo));
	if (ft_parse(argc, argv, &data))
		return (ft_handler("parse() error\n"));
	if (init_all(&data, &philos))
		return (ft_handler("init() error\n"));
	if (init_main(&data, &philos))
		return (FAILURE);
	return (SUCESS);
}
