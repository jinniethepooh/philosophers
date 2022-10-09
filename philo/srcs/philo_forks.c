/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <cchetana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 23:07:18 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/08 15:42:19 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks_back(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	look_for_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->log);
	if (philo->end->found)
	{
		pthread_mutex_unlock(&philo->log);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"has taken a fork\n");
	pthread_mutex_unlock(&philo->log);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->log);
	if (philo->end->found)
	{
		pthread_mutex_unlock(&philo->log);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"has taken a fork\n");
	pthread_mutex_unlock(&philo->log);
	return (0);
}

static int	fork_init(pthread_mutex_t *f, int n_philo)
{
	int	n;

	n = 0;
	while (n < n_philo)
	{
		if (pthread_mutex_init(&f[n], NULL))
			return (thread_init_error());
		n++;
	}
	return (0);
}

int	assign_forks(t_philo *philo, int n_philo)
{
	int	n;

	if (fork_init(philo[0].used_fork, n_philo))
		return (thread_init_error());
	n = 0;
	if (n_philo == 1)
	{
		philo[n].left_fork = &philo[n].used_fork[n];
		philo[n].right_fork = &philo[n].used_fork[n];
		return (0);
	}
	while (n < n_philo)
	{
		philo[n].left_fork = &philo[n].used_fork[n];
		philo[n].right_fork = &philo[n].used_fork[(n + 1) % n_philo];
		n++;
	}
	return (0);
}
