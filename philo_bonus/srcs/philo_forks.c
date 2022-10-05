/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 23:07:18 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 15:36:55 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	put_forks_back(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	look_for_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"has taken a fork\n");
	sem_post(philo->dead);
	sem_wait(philo->forks);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"has taken a fork\n");
	sem_post(philo->dead);
}
