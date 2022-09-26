/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:37:30 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/27 01:09:46 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (gap < philo->info->time_to.die);
}
