/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:13:38 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 02:39:04 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	end_point_found(t_philo *philo, t_timeval now)
{
	return ((!still_alive(now, philo) && !philo->end->found) || \
				philo->end->limit_counter == philo->info.n_philo);
}

void	*hp_tracker(void *philo_addr)
{
	t_philo		*philo;
	t_timeval	now;

	philo = (t_philo *)philo_addr;
	while (!philo->end->found)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&(philo->end->dead_lock));
		if (end_point_found(philo, now))
		{
			philo->end->found = philo->s_philo;
			if (philo->end->limit_counter != philo->info.n_philo)
				print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
					"died\n");
			pthread_mutex_unlock(&(philo->end->dead_lock));
			put_forks_back(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->end->dead_lock));
	}
	return (NULL);
}

static void	sleep_cycle(t_philo *philo)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	if (!philo->end->found)
	{
		print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
			"is sleeping\n");
		usleep(philo->info.time_to.sleep * 1000);
		if (philo->end->found)
			return ;
		gettimeofday(&now, NULL);
		print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
			"is thinking\n");
	}
}

static void	eat_cycle(t_philo *philo)
{
	t_timeval	now;

	if (!philo->l_fork || !philo->r_fork)
	{
		look_for_forks(philo, &(philo->l_fork), 'l');
		look_for_forks(philo, &(philo->r_fork), 'r');
	}
	if (!philo->end->found)
	{
		gettimeofday(&now, NULL);
		print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
			"is eating\n");
		philo->hp = now;
		philo->n_ate += 1;
		if (philo->n_ate == philo->info.time_to.n_eat)
			philo->end->limit_counter += 1;
		usleep(philo->info.time_to.eat * 1000);
		put_forks_back(philo);
	}
}

void	*life_cycle(void *philo_addr)
{
	t_philo		*philo;
	pthread_t	hp_tracking;

	philo = philo_addr;
	if (pthread_create(&hp_tracking, NULL, &hp_tracker, philo))
		return (NULL);
	while (!philo->end->found)
	{
		eat_cycle(philo);
		sleep_cycle(philo);
	}
	pthread_detach(hp_tracking);
	return (NULL);
}
