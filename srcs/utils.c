/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:35:46 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 00:02:40 by cchetana         ###   ########.fr       */
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

void	print_log(int s_philo, long timestamp, const char *act)
{
	printf(BLU" %-10ld" CYN " %-5d" WHT " %s" RES, timestamp, s_philo, act);
}
