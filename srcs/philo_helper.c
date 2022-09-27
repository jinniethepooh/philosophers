/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:35:46 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 19:30:33 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	nbr;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	sign = 1;
	nbr = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		sign = ',' - str[i++];
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		if (nbr >= ULLONG_MAX && sign > 0)
			return (-1);
		if (nbr > ULLONG_MAX && sign < 0)
			return (0);
		++i;
	}
	return (nbr * sign);
}

int	get_timestamp(time_v now, time_v then)
{
	int	gap;

	gap = (now.tv_sec - then.tv_sec) * 1000;
	gap += (now.tv_usec - then.tv_usec) / 1000;
	return (gap);
}

int	still_alive(time_v now, t_philo *philo)
{
	int		gap;
	time_v	then;

	then = philo->hp;
	gap = get_timestamp(now, then);
	return (gap < philo->info.time_to.die);
}

void	print_log(int s_philo, long timestamp, const char *act)
{
	printf(BLU" %-10ld" CYN " %-5d" WHT " %s" RES, timestamp, s_philo, act);
}
