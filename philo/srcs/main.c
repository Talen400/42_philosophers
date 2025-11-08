/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 01:19:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/08 04:09:27 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_philo()
{

}

int	main(int argc, char **argv)
{
	t_data_time	times;

	if (ft_parse(argc, argv, &times))
		return (FAIL);
	ft_init_philo(times);
	return (SUCESS);
}
