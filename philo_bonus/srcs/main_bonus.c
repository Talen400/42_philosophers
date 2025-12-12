/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:11 by tlavared          #+#    #+#             */
/*   Updated: 2025/12/12 16:27:38 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * kill all process :>
 */

static void	kill_all_processes(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (philos[i].pid > 0)
			kill(philos[i].pid, SIGKILL);
		i++;
	}
}

/*
 * To Father wait all process finish
 *
 * note: create a alternative to WIFEXITED and WIFESTATUS
 */

static void	wait_for_process(t_philo *philos, t_data *data)
{
	size_t	i;
	int		status;
	int		someone_died;

	someone_died = FALSE;
	i = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				someone_died = TRUE;
				kill_all_processes(philos, data->n_philo);
				break ;
			}
		}
		i++;
	}
}

/*
 * Routine of father process
 */

int	main_routine(t_data *data, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < data->n_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			kill_all_processes(philos, i);
			free(philos);
			destroy_semaphores(data);
			return (FAILURE);
		}
		else if (philos[i].pid == 0)
		{
			philo_process(&philos[i]);
			exit(0);
		}
		i++;
	}
	wait_for_process(philos, data);
	destroy_semaphores(data);
	return (SUCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;

	memset(&data, 0, sizeof(t_data));
	if (ft_parse(argc, argv, &data))
		return (ft_handler("parse() error\n"));
	if (init_all(&data, &philos))
		return (ft_handler("init() error\n"));
	if (main_routine(&data, philos))
		return (FAILURE);
	destroy_all(&data, philos);
	return (SUCESS);
}
