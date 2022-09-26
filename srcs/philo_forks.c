/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 23:07:18 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 01:19:45 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_fork_index(t_philo *philo, char side);

void	put_back_forks(t_philo *philo)
{
	int	l_index;
	int	r_index;

	philo->l_fork = 0;
	philo->r_fork = 0;
	if (philo->info->n_philo == 1)
	{
		pthread_mutex_unlock(&(philo->used_fork[0]));
		return ;
	}
	l_index = get_fork_index(philo, 'l');
	r_index = get_fork_index(philo, 'r');
	pthread_mutex_unlock(&(philo->used_fork[l_index]));
	pthread_mutex_unlock(&(philo->used_fork[r_index]));
}

static int	get_fork_index(t_philo *philo, char side)
{
	if (philo->info->n_philo == 1)
		return (0);
	if (philo->s_philo == philo->info->n_philo)
	{
		if (side == 'l')
			return (0);
		if (side == 'r')
			return (philo->s_philo - 1);
	}
	if (side == 'l')
		return (philo->s_philo - 1);
	if (side == 'r')
		return (philo->s_philo);
	return (0);
}

void	look_for_forks(t_philo *philo, int *fork, char side)
{
	time_v	now;
	int		index;

	index = get_fork_index(philo, side);
	pthread_mutex_lock(&(philo->used_fork[index]));
	if (philo->dead->found)
	{
		pthread_mutex_unlock(&(philo->used_fork[index]));
		return ;
	}
	gettimeofday(&now, NULL);
	philo->hp = now;
	print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
		"has taken a fork\n");
	*fork = 1;
}