/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:19:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/13 02:15:44 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	size_t	i;

	if (ft_parse(argc, argv, &data))
		return (ft_handler("parse() error\n"));
	if (init_all(&data, &philos))
		return (ft_handler("init() error\n"));
	i = -1;
	while (++i < data.n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
		{
			destroy_all(&data, philos);
			return (ft_handler("thead creatiion failed\n"));
		}
	}
	i = -1;
	while (++i < data.n_philo)
		pthread_join(philos[i].thread, NULL);
	destroy_all(&data, philos);
	return (SUCESS);
}
