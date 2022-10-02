/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:13:38 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 00:56:06 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*limit_tracker(void *philo_addr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_addr;
	i = 0;
	while (i < philo->info.n_philo)
	{
		sem_wait(philo->limit);
		i++;
	}
	sem_post(philo->end);
	return (NULL);
}

void	*hp_tracker(void *philo_addr)
{
	t_philo	*philo;
	time_v	now;

	philo = (t_philo *)philo_addr;
	while (1)
	{
		gettimeofday(&now, NULL);
		sem_wait(philo->dead);
		if (!still_alive(now, philo))
		{
			print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
				"died\n");
			put_forks_back(philo);
			sem_post(philo->end);
			return (NULL);
		}
		sem_post(philo->dead);
	}
	return (NULL);
}

static void	sleep_cycle(t_philo *philo)
{
	time_v	now;

	gettimeofday(&now, NULL);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
		"is sleeping\n");
	sem_post(philo->dead);
	usleep(philo->info.time_to.sleep * 1000);
	gettimeofday(&now, NULL);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
		"is thinking\n");
	sem_post(philo->dead);
}

static void	eat_cycle(t_philo *philo)
{
	time_v	now;

	if (!philo->l_fork || !philo->r_fork)
		look_for_forks(philo);
	gettimeofday(&now, NULL);
	sem_wait(philo->dead);
	print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
		"is eating\n");
	sem_post(philo->dead);
	philo->hp = now;
	philo->n_ate += 1;
	if (philo->n_ate == philo->info.time_to.n_eat)
		sem_post(philo->limit);
	usleep(philo->info.time_to.eat * 1000);
	put_forks_back(philo);
}

int	life_cycle(t_philo	*philo)
{
	if (philo->s_philo == 1)
		if (limit_tracker_init(philo, philo->info.time_to.n_eat))
			return (1);
	if (hp_tracker_init(philo))
		return (1);
	while (1)
	{
		eat_cycle(philo);
		sleep_cycle(philo);
	}
	return (0);
}
