/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:49 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 01:04:59 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	**philo;
	int		n_philo;

	if (is_validinput(argc, argv))
	{
		n_philo = ft_atoi(argv[1]);
		philo = (t_philo **)malloc(sizeof(t_philo *) * (n_philo + 1));
		if (!philo)
			return (malloc_error());
		philo_init(philo, n_philo, argc, argv);
		free_at_exit(philo);
	}
	return (0);
}
