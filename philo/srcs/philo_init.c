/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <cchetana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:48:39 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/08 15:54:12 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_init(t_philo *philo, int n_philo)
{
	int			n;
	pthread_t	hp_tracking;

	n = 0;
	while (n < n_philo)
	{
		if (pthread_create(&philo[n].life, NULL, &life_cycle, &philo[n]))
			return (thread_init_error());
		n++;
		usleep(50);
	}
	if (pthread_create(&hp_tracking, NULL, &hp_tracker, philo))
		return (thread_init_error());
	n = 0;
	while (n < n_philo)
	{
		if (pthread_join(philo[n].life, NULL))
			return (thread_init_error());
		n++;
	}
	if (pthread_join(hp_tracking, NULL))
		return (thread_init_error());
	return (0);
}

static void	get_time_philo(t_philo *philo, int n_philo)
{
	t_timeval	now;
	int			n;

	gettimeofday(&now, NULL);
	n = 0;
	while (n < n_philo)
	{
		philo[n].kickoff = now;
		philo[n].hp = now;
		n++;
	}
}

static void	get_general_info(t_philo *philo, t_philo *info)
{
	philo->used_fork = info->used_fork;
	philo->end = info->end;
	philo->info.n_philo = info->info.n_philo;
	philo->info.time_to.die = info->info.time_to.die;
	philo->info.time_to.eat = info->info.time_to.eat;
	philo->info.time_to.sleep = info->info.time_to.sleep;
	philo->info.time_to.n_eat = info->info.time_to.n_eat;
	philo->n_ate = 0;
}

int	philo_init(t_philo *philo, t_philo philo_tmp, int n_philo)
{
	int		n;

	n = 0;
	while (n < n_philo)
	{
		philo[n].s_philo = n + 1;
		get_general_info(&philo[n], &philo_tmp);
		if (pthread_mutex_init(&philo[n].log, NULL))
			return (thread_init_error());
		n++;
	}
	if (assign_forks(philo, n_philo))
		return (1);
	get_time_philo(philo, n_philo);
	if (thread_init(philo, n_philo))
		return (1);
	return (0);
}
