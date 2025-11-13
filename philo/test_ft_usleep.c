/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_usleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 02:09:06 by tlavared          #+#    #+#             */
/*   Updated: 2025/11/13 02:15:22 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < milliseconds)
		usleep(500);
}

int	main(void)
{
	long	start;
	long	end;
	int		i;

	printf("========== test usleep() ==========\n");
	i = -1;
	while (++i < 20)
	{
		start = get_time_ms();
		usleep(200000);
		end = get_time_ms();
		printf("Teste %2d: %3ld ms (erro: %+3ld ms)\n",
			i + 1, end - start, (end - start) - 200);
	}
	printf("\n========== test ft_usleep() ==========\n");
	i = -1;
	while (++i < 20)
	{
		start = get_time_ms();
		ft_usleep(200);
		end = get_time_ms();
		printf("Teste %2d: %3ld ms (erro: %+3ld ms)\n",
			1, end - start, (end - start) - 200);
	}
	return (0);
}
