/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:28:35 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 15:19:18 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_mutual(t_philo *philo)
{
	sem_close(philo->dead);
	sem_close(philo->end);
	sem_close(philo->forks);
	sem_close(philo->limit);
}

static void	error_msg(int exit_code)
{
	if (exit_code == 1)
		printf("[ERROR] could not malloc\n");
	else if (exit_code == 2)
		printf("[ERROR] could not properly initialize\n");
	else if (exit_code == 3)
		printf("[ERROR] could not properly process\n");
}

int	free_at_exit(t_philo **philo, int *f_pid, int exit_code)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		if (i == 0)
			free_mutual(philo[i]);
		free(philo[i]);
		i++;
	}
	free(philo);
	if (f_pid)
		free(f_pid);
	error_msg(exit_code);
	return (exit_code);
}

int	input_error(void)
{
	printf(BRED"[ERROR]"RED" invalid input\n"RES);
	printf("./philo_bonus [1] [2] [3] [4] [5]\n");
	printf("[1] no. of philos\n");
	printf("[2] time to die\n");
	printf("[3] time to eat\n");
	printf("[4] time to sleep\n");
	printf("[5] (optional) number of times each philo must eat\n");
	return (0);
}
