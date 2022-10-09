/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <cchetana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:48:39 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/08 18:20:57 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	limit_tracker_init(t_philo *philo, int time_to_eat)
{
	pthread_t	limit_tracking;

	if (time_to_eat != -1)
	{
		if (pthread_create(&limit_tracking, NULL, &limit_tracker, philo))
			return (1);
		pthread_detach(limit_tracking);
	}
	return (0);
}

int	hp_tracker_init(t_philo *philo)
{
	pthread_t	hp_tracking;

	if (pthread_create(&hp_tracking, NULL, &hp_tracker, philo))
		return (1);
	pthread_detach(hp_tracking);
	return (0);
}

static void	get_general_input(t_philo *philo, int argc, char **argv)
{
	philo->info.n_philo = ft_atoi(argv[1]);
	philo->info.time_to.die = ft_atoi(argv[2]);
	philo->info.time_to.eat = ft_atoi(argv[3]);
	philo->info.time_to.sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->info.time_to.n_eat = ft_atoi(argv[5]);
	else
		philo->info.time_to.n_eat = -1;
	if (philo->info.time_to.n_eat == 0)
		philo->info.time_to.n_eat = 1;
	philo->n_ate = 0;
}

static int	semaphore_init(t_semaphore *tmp, int n_philo)
{
	sem_unlink("death");
	sem_unlink("end");
	sem_unlink("forks");
	sem_unlink("limit");
	tmp->dead = sem_open("death", O_CREAT | O_EXCL, 0644, 1);
	if (tmp->dead == SEM_FAILED)
		return (3);
	tmp->end = sem_open("end", O_CREAT | O_EXCL, 0644, 0);
	if (tmp->end == SEM_FAILED)
		return (3);
	tmp->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, n_philo);
	if (tmp->forks == SEM_FAILED)
		return (3);
	tmp->limit = sem_open("limit", O_CREAT | O_EXCL, 0644, 0);
	if (tmp->limit == SEM_FAILED)
		return (3);
	return (0);
}

int	philo_init(t_philo **philo, int n_philo, int argc, char **argv)
{
	int			n;
	t_timeval	now;
	t_semaphore	tmp;

	if (semaphore_init(&tmp, n_philo))
		return (3);
	n = 0;
	gettimeofday(&now, NULL);
	while (n < n_philo)
	{
		philo[n]->kickoff = now;
		philo[n]->hp = now;
		philo[n]->s_philo = n + 1;
		philo[n]->dead = tmp.dead;
		philo[n]->limit = tmp.limit;
		philo[n]->forks = tmp.forks;
		philo[n]->end = tmp.end;
		get_general_input(philo[n], argc, argv);
		n++;
	}
	philo[n] = NULL;
	return (0);
}
