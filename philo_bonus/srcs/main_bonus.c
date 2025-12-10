/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/10 08:25:25 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data		data;
//	t_philo		*philos;

	if (ft_parse(argc, argv, &data))
		return (ft_handler("parse() error\n"));
	/*
	if (init_all(&data, &philos))
		return (ft_handler("init() error\n"));
	if (init_main(&data, &philos))
		return (FAILURE);
	return (SUCESS);
	*/
	printf("Hello, world! :> \n");
}
