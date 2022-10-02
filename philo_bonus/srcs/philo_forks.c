/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 23:07:18 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 02:42:33 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	put_forks_back(t_philo *philo)
{
	philo->l_fork = 0;
	philo->r_fork = 0;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	look_for_forks(t_philo *philo)
{
	t_timeval	now;

	sem_wait(philo->forks);
	gettimeofday(&now, NULL);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
		"has taken a fork\n");
	sem_post(philo->dead);
	sem_wait(philo->forks);
	gettimeofday(&now, NULL);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
		"has taken a fork\n");
	sem_post(philo->dead);
	philo->l_fork = 1;
	philo->r_fork = 1;
}
