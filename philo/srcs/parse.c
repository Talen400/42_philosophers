/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 02:05:15 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/13 00:54:35 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * Parse the argument:
 *  42 => okay!
 *  42a or 4a2 or a42 = wrong :<
 *
 */

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

static long	ft_atoil(const char *nptr)
{
	char	*str;
	int		sign;
	long	integer;

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

static int	ft_check_str(int argc, char **argv)
{
	int	i;
	int	len;

	len = 1;
	while (len < argc)
	{
		i = 0;
		while (argv[len][i])
		{
			if (!ft_isdigit((argv[len][i])))
			{
				return (FAIL);
			}
			i++;
		}
		len++;
	}
	return (SUCESS);
}

int	ft_parse(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6 || ft_check_str(argc, argv))
		return (FAIL);
	data->n_philo = ft_atoil(argv[1]);
	data->die = ft_atoil(argv[2]);
	data->eat = ft_atoil(argv[3]);
	data->sleep = ft_atoil(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoil(argv[5]);
	else
		data->must_eat = 0;
	return (SUCESS);
}
