/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <cchetana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:35:46 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/08 18:44:13 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

unsigned long	get_timestamp(t_timeval now, t_timeval then)
{
	unsigned long	gap;

	gap = (now.tv_sec - then.tv_sec) * 1000;
	gap = gap + (now.tv_usec - then.tv_usec) / 1000;
	return (gap);
}

t_timeval	get_now(void)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

unsigned long	get_now_val(void)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return ((unsigned long)(now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	adj_usleep(unsigned long time_to_ms)
{
	unsigned long	time;

	time = get_now_val();
	usleep(time_to_ms * 900);
	while (get_now_val() <= time + time_to_ms)
		usleep(1);
}
