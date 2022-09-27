/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:28:35 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 19:30:23 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_at_exit(t_philo **philo)
{
	int	i;

	i = 0;
	if (philo)
	{
		while (philo[i])
		{
			if (!i)
			{
				if (philo[i]->used_fork)
					free(philo[i]->used_fork);
				if (philo[i]->dead)
					free(philo[i]->dead);
			}
			free(philo[i++]);
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
