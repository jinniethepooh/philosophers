/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:28:35 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 01:10:06 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	free_2d(void **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr && arr[i])
// 		free(arr[i++]);
// 	free(arr);
// }

static void	free_fork(t_philo *philo)
{
	if (philo->used_fork)
	{
		free(philo->used_fork);
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
			if (!i)
				free_fork(philo[i]);
			if (philo[i]->info)
				free(philo[i]->info);
			free(philo[i++]);
		}
	}
	free(philo);
}

int	malloc_error(void)
{
	printf("[ERROR] could not malloc\n");
	return (1);
}

void	invalid_input_msg(void)
{
	printf(BRED"[ERROR]"RED" invalid input\n"RES);
	printf(MAG"./philo [no. of philos] [time_to_die]");
	printf(" [time_to_eat] [time_to_sleep]");
	printf(" opt[number_of_times_each_philo_must_eat]\n"RES);
	// free_at_exit();
	// return ;
}

int	error_input(void)
{
	printf(BRED"[ERROR]"RED" invalid input\n"RES);
	printf(MAG"./philo [no. of philos] [time_to_die]");
	printf(" [time_to_eat] [time_to_sleep]");
	printf(" opt[number_of_times_each_philo_must_eat]\n"RES);
	// free_at_exit();
	return (0);
}
