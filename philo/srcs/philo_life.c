/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <cchetana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:13:38 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/08 17:39:47 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	end_point_found(t_philo *philo, t_timeval now)
{
	if (!still_alive(now, philo) && !philo->end->found)
		return (philo->s_philo);
	if (philo->end->limit_counter == philo->info.n_philo)
		return (-1);
	return (0);
}

void	*hp_tracker(void *philo_addr)
{
	t_philo	*philo;
	int		n;

	philo = (t_philo *)philo_addr;
	while (1)
	{
		n = 0;
		while (n < philo[0].info.n_philo)
		{
			pthread_mutex_lock(&philo[n].log);
			philo[n].end->found = end_point_found(&philo[n], get_now());
			if (philo[n].end->found)
			{
				if (philo[n].end->found == philo[n].s_philo)
					print_log(philo[n].s_philo, get_timestamp(get_now(), \
						philo[n].kickoff), "died\n");
				pthread_mutex_unlock(&philo[n].log);
				put_forks_back(&philo[n]);
				return (NULL);
			}
			pthread_mutex_unlock(&philo[n].log);
			n++;
		}
	}
	return (NULL);
}

static int	sleep_cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->log);
	if (philo->end->found)
		return (pthread_mutex_unlock(&philo->log));
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"is sleeping\n");
	pthread_mutex_unlock(&philo->log);
	adj_usleep(philo->info.time_to.sleep);
	pthread_mutex_lock(&philo->log);
	if (philo->end->found)
		return (pthread_mutex_unlock(&philo->log));
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"is thinking\n");
	pthread_mutex_unlock(&philo->log);
	return (0);
}

static int	eat_cycle(t_philo *philo)
{
	pthread_mutex_lock(&philo->log);
	philo->hp = get_now();
	if (philo->end->found)
		return (pthread_mutex_unlock(&philo->log));
	print_log(philo->s_philo, get_timestamp(get_now(), philo->kickoff), \
		"is eating\n");
	philo->n_ate += 1;
	if (philo->n_ate == philo->info.time_to.n_eat)
		philo->end->limit_counter += 1;
	pthread_mutex_unlock(&philo->log);
	adj_usleep(philo->info.time_to.eat);
	put_forks_back(philo);
	return (0);
}

void	*life_cycle(void *philo_addr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_addr;
	while (1)
	{
		if (look_for_forks(philo))
			break ;
		if (eat_cycle(philo))
			break ;
		if (sleep_cycle(philo))
			break ;
	}
	return (NULL);
}
