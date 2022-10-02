/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:49 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 02:30:54 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	**prep_philo(int n_philo)
{
	t_philo	**philo;
	int		n;

	philo = (t_philo **)malloc(sizeof(t_philo *) * (n_philo + 1));
	if (!philo)
		return (malloc_error());
	n = 0;
	while (n < n_philo)
	{
		philo[n] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[n])
			return (malloc_error());
		n++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	**philo;
	int		n_philo;

	if (is_validinput(argc, argv))
	{
		n_philo = ft_atoi(argv[1]);
		philo = prep_philo(n_philo);
		if (!philo)
		{
			free_at_exit(philo);
			return (1);
		}
		philo_init(philo, n_philo, argc, argv);
		free_at_exit(philo);
	}
	return (0);
}
