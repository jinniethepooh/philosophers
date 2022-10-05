/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:49 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 16:39:26 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(int s_philo, unsigned long timestamp, const char *act)
{
	printf(BLU" %-10ld" CYN " %-5d" WHT " %s" RES, timestamp, s_philo, act);
}

static void	get_general_info(t_philo *philo_tmp, int argc, char **argv)
{
	philo_tmp->info.n_philo = ft_atoi(argv[1]);
	philo_tmp->info.time_to.die = ft_atoi(argv[2]);
	philo_tmp->info.time_to.eat = ft_atoi(argv[3]);
	philo_tmp->info.time_to.sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_tmp->info.time_to.n_eat = ft_atoi(argv[5]);
	else
		philo_tmp->info.time_to.n_eat = -1;
	if (philo_tmp->info.time_to.n_eat == 0)
		philo_tmp->info.time_to.n_eat = 1;
}

static int	philo_prep(t_philo *philo_tmp, int n_philo, int argc, char **argv)
{
	philo_tmp->used_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
								* n_philo);
	if (!philo_tmp->used_fork)
		return (malloc_error());
	philo_tmp->end = (t_end *)malloc(sizeof(t_end));
	if (!philo_tmp->end)
		return (malloc_error());
	philo_tmp->end->found = 0;
	philo_tmp->end->limit_counter = 0;
	get_general_info(philo_tmp, argc, argv);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_philo	philo_tmp;
	int		n_philo;

	if (is_validinput(argc, argv))
	{
		n_philo = ft_atoi(argv[1]);
		philo = (t_philo *)malloc(sizeof(t_philo) * n_philo);
		if (philo)
		{
			if (philo_prep(&philo_tmp, n_philo, argc, argv))
				return (1);
			if (philo_init(philo, philo_tmp, n_philo))
				return (1);
			free_at_exit(philo);
		}
		else
			return (malloc_error());
	}
	return (0);
}
