/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:28:35 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 14:34:20 by cchetana         ###   ########.fr       */
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
			pthread_mutex_unlock(&philo->used_fork[i]);
			pthread_mutex_destroy(&philo->used_fork[i]);
			i++;
		}
		free(philo->used_fork);
	}
	if (philo->end)
		free(philo->end);
}

void	free_at_exit(t_philo *philo)
{
	int	n;

	n = 0;
	if (philo)
	{
		while (n < philo[0].info.n_philo)
		{
			if (n == 0)
				free_mutual(&philo[n]);
			pthread_detach(philo[n].life);
			pthread_mutex_destroy(&philo[n].log);
			n++;
		}
	}
	free(philo);
}

int	malloc_error(void)
{
	printf("[ERROR] could not malloc\n");
	return (1);
}

int	thread_init_error(void)
{
	printf("[ERROR] could not initialize thread / mutex\n");
	return (1);
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
