/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:49:58 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/07 18:25:51 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		sign;
	int		integer;

	str = (char *) nptr;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	integer = 0;
	while (ft_isdigit(*str))
	{
		integer = integer * 10 +(*str - '0');
		str++;
	}
	return (integer * sign);
}

int	ft_parse(int argc, char **argv, t_data_time *times)
{
	if (argc < 5 | argc > 6)
	{
		printf("error\n");
		return (FAIL);
	}
	times->n_philo = ft_atoi(argv[1]);
	times->die = ft_atoi(argv[2]);
	times->eat = ft_atoi(argv[3]);
	times->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		times->must_eat =ft_atoi(argv[5]);
	else
		times->must_eat = 0;
	printf("%zu\n", times->n_philo);
	printf("%zu\n", times->die);
	printf("%zu\n", times->eat);
	printf("%zu\n", times->sleep);
	printf("%zu\n", times->must_eat);
	return (SUCESS);
}
