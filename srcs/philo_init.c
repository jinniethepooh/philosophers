/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:48:39 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 01:35:51 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t *fork_init(int n_philo)
{
	int					i;
	pthread_mutex_t		*f;

	f = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!f)
		invalid_input_msg();
	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&f[i], NULL))
			invalid_input_msg();
		i++;
	}
	return (f);
}

static t_death *death_init(void)
{
	t_death		*d;

	d = (t_death *)malloc(sizeof(t_death));
	if (pthread_mutex_init(&(d->lock), NULL))
		invalid_input_msg();
	d->found = 0;
	return (d);
}

static void	get_general_input(t_philo *philo, time_v now, int argc, char **argv)
{
	philo->kickoff = now;
	philo->hp = now;
	philo->l_fork = 0;
	philo->r_fork = 0;
	philo->n_ate = 0;
	philo->cur_act = 'e';
	philo->info = (t_info *)malloc(sizeof(t_info));
	if (!philo->info)
		invalid_input_msg();
	philo->info->n_philo = ft_atoi(argv[1]);
	philo->info->time_to.die = ft_atoi(argv[2]);
	philo->info->time_to.eat = ft_atoi(argv[3]);
	philo->info->time_to.sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->info->time_to.n_eat = atoi(argv[5]);
	else
		philo->info->time_to.n_eat = -1;
}

static void	thread_init(t_philo **philo, int n_philo)
{
	int	n;

	n = 0;
	while (n < n_philo)
	{
		if (pthread_create(&(philo[n]->life), NULL, &life_cycle, philo[n]))
			invalid_input_msg();	// to change to other error-type
		usleep(10);
		n++;
	}
	n = 0;
	while (n < n_philo)
	{
		if (pthread_join(philo[n]->life, NULL))
			invalid_input_msg();	// to change to other error-type
		n++;
	}
}

void	philo_init(t_philo **philo, int n_philo, int argc, char **argv)
{
	int					n;
	time_v				now;
	pthread_mutex_t		*f;
	t_death				*d;

	n = 0;
	gettimeofday(&now, NULL);
	f = fork_init(n_philo);
	d = death_init();
	while (n < n_philo)
	{
		philo[n] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[n])
			invalid_input_msg();	// to change to other error-type
		philo[n]->s_philo = n + 1;
		get_general_input(philo[n], now, argc, argv);
		philo[n]->used_fork = f;
		philo[n]->dead = d;
		n++;
	}
	philo[n] = NULL;
	thread_init(philo, n_philo);
}
