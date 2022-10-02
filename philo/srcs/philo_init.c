/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:48:39 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 02:26:39 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t *fork_init(int n_philo)
{
	int					i;
	pthread_mutex_t		*f;

	f = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!f)
		return (malloc_error());
	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&f[i], NULL))
			return (thread_init_error());
		i++;
	}
	return (f);
}

static t_end *end_init(void)
{
	t_end		*e;

	e = (t_end *)malloc(sizeof(t_end));
	if (!e)
		return (malloc_error());
	if (pthread_mutex_init(&(e->dead_lock), NULL))
		return (thread_init_error());
	e->found = 0;
	e->limit_counter = 0;
	return (e);
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
	philo->l_fork = 0;
	philo->r_fork = 0;
	philo->n_ate = 0;
}

static void	*thread_init(t_philo **philo, int n_philo)
{
	int	n;

	n = 0;
	while (n < n_philo)
	{
		if (pthread_create(&(philo[n]->life), NULL, &life_cycle, philo[n]))
			return (thread_init_error());
		usleep(5);
		n++;
	}
	n = 0;
	while (n < n_philo)
	{
		if (pthread_join(philo[n]->life, NULL))
			return (thread_init_error());
		n++;
	}
	return (NULL);
}

void	philo_init(t_philo **philo, int n_philo, int argc, char **argv)
{
	int					n;
	time_v				now;
	t_end				*e;
	pthread_mutex_t		*f;

	n = 0;
	gettimeofday(&now, NULL);
	f = fork_init(n_philo);
	e = end_init();
	if (!f || !e)
		return ;
	while (n < n_philo)
	{
		philo[n]->kickoff = now;
		philo[n]->hp = now;
		philo[n]->s_philo = n + 1;
		philo[n]->used_fork = f;
		philo[n]->end = e;
		get_general_input(philo[n], argc, argv);
		n++;
	}
	philo[n] = NULL;
	thread_init(philo, n_philo);
}
