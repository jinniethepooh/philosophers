/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:14:16 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/09 12:38:59 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
				c == ' ');
}

int	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

static int	loop_checker(char *av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i] && ft_isspace(i))
		i++;
	while (av[i] && av[i] == '+')
		i++;
	if (!av[i])
		return (0);
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (av[i])
		return (0);
	return (1);
}

int	is_validinput(int ac, char **av)
{
	int	i;

	if (!av || ac < 5 || ac > 6)
		return (input_error());
	if (ft_atoi(av[1]) == 0)
		return (input_error());
	i = 1;
	while (av[i])
	{
		if (!loop_checker(av[i]))
			return (input_error());
		i++;
	}
	return (1);
}

int	still_alive(t_timeval now, t_philo *philo)
{
	unsigned long	gap;
	t_timeval		then;

	then = philo->hp;
	gap = get_timestamp(now, then);
	return (gap <= philo->info.time_to.die);
}
