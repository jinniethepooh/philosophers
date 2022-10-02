/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:28:35 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 02:23:34 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutual(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->used_fork)
	{
		while (i < philo->info.n_philo)
		{
			pthread_mutex_destroy(&(philo->used_fork[i]));
			i++;
		}
		free(philo->used_fork);
	}
	if (philo->end)
	{
		pthread_mutex_destroy(&(philo->end->dead_lock));
		free(philo->end);
	}
}

void	free_at_exit(t_philo **philo)
{
	int	i;

	i = 0;
	if (philo)
	{
		while (philo[i])
		{
			if (i == 0)
				free_mutual(philo[i]);
			pthread_detach(philo[i]->life);
			free(philo[i]);
			i++;
		}
	}
	free(philo);
}

void	*malloc_error(void)
{
	printf("[ERROR] could not malloc\n");
	return (NULL);
}

void	*thread_init_error(void)
{
	printf("[ERROR] could not initialize thread / mutex\n");
	return (NULL);
}

int	error_input(void)
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
