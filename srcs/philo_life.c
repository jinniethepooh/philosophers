/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:13:38 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 01:39:35 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*hp_tracker(void *philo_addr)
{
	t_philo	*philo;
	time_v	now;

	philo = (t_philo *)philo_addr;
	while (!philo->dead->found)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&(philo-> dead->lock));
		if (!still_alive(now, philo) && !philo->dead->found)
		{
			philo->dead->found = philo->s_philo;
			print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
				"died\n");
			pthread_mutex_unlock(&(philo->dead->lock));
			put_forks_back(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->dead->lock));
	}
	return (NULL);
}

static void	sleep_cycle(t_philo *philo)
{
	time_v	now;

	gettimeofday(&now, NULL);
	if (philo->cur_act == 's' && !philo->dead->found)
	{
		print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
			"is sleeping\n");
		usleep(philo->info->time_to.sleep * 1000);
		if (philo->dead->found)
			return ;
		gettimeofday(&now, NULL);
		print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
			"is thinking\n");
		philo->cur_act = 'e';
	}
}

static int	still_eating(t_philo *philo)
{
	if (philo->info->time_to.n_eat == -1)
		return (1);
	if (philo->n_ate < philo->info->time_to.n_eat)
		return (1);
	return (0);
}

static void	eat_cycle(t_philo *philo)
{
	time_v	now;

	gettimeofday(&now, NULL);
	if (philo->cur_act == 'e' && still_eating(philo))
	{
		while ((!philo->l_fork || !philo->r_fork) && !philo->dead->found)
		{
			look_for_forks(philo, &(philo->l_fork), 'l');
			look_for_forks(philo, &(philo->r_fork), 'r');
		}
		if (!philo->dead->found)
		{
			gettimeofday(&now, NULL);
			print_log(philo->s_philo, get_timestamp(now, philo->kickoff), \
				"is eating\n");
			philo->hp = now;
			philo->n_ate += 1;
			usleep(philo->info->time_to.eat * 1000);
			put_forks_back(philo);
			philo->cur_act = 's';
		}
	}
}

void	*life_cycle(void *philo_addr)
{
	t_philo		*philo;
	pthread_t	hp_tracking;

	philo = philo_addr;
	pthread_create(&hp_tracking, NULL, &hp_tracker, philo);	// to have error handler
	while (!philo->dead->found)
	{
		sleep_cycle(philo);
		eat_cycle(philo);
	}
	pthread_detach(hp_tracking);
	return (NULL);
}
