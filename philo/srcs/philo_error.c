/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:28:35 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/28 18:23:15 by cchetana         ###   ########.fr       */
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
	if (philo->dead)
	{
		pthread_mutex_destroy(&(philo->dead->lock));
		free(philo->dead);
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
	printf(MAG"./philo [no. of philos] [time_to_die]");
	printf(" [time_to_eat] [time_to_sleep]");
	printf(" opt[number_of_times_each_philo_must_eat]\n"RES);
	return (0);
}
