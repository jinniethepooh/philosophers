/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:36:49 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 15:24:54 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(int s_philo, unsigned long timestamp, const char *act)
{
	printf(BLU" %-10ld" CYN " %-5d" WHT " %s" RES, timestamp, s_philo, act);
}

static int	cycle_end(int *f_pid, int n_philo)
{
	int	n;

	n = 0;
	while (n < n_philo)
	{
		if (kill(f_pid[n], SIGKILL))
			return (2);
		n++;
	}
	return (0);
}

static int	fork_philo(t_philo **philo, int *f_pid, int n_philo)
{
	int	n;

	n = 0;
	while (n < n_philo)
	{
		f_pid[n] = fork();
		if (f_pid[n] < 0)
			return (2);
		if (f_pid[n] == 0)
		{
			if (life_cycle(philo[n]))
				return (1);
			break ;
		}
		n++;
	}
	sem_wait(philo[0]->end);
	return (cycle_end(f_pid, n_philo));
}

static t_philo	**prep_philo(int n_philo)
{
	t_philo	**philo;
	int		n;

	philo = (t_philo **)malloc(sizeof(t_philo *) * (n_philo + 1));
	if (!philo)
		return (NULL);
	n = 0;
	while (n < n_philo)
	{
		philo[n] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[n])
			return (NULL);
		n++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo		**philo;
	int			n_philo;
	int			*f_pid;

	if (is_validinput(argc, argv))
	{
		n_philo = ft_atoi(argv[1]);
		philo = prep_philo(n_philo);
		f_pid = (int *)malloc(sizeof(int) * n_philo);
		if (!philo || !f_pid)
			return (free_at_exit(philo, f_pid, 1));
		if (philo_init(philo, n_philo, argc, argv))
			return (free_at_exit(philo, f_pid, 2));
		if (fork_philo(philo, f_pid, n_philo))
			return (free_at_exit(philo, f_pid, 3));
		free_at_exit(philo, f_pid, 0);
	}
	return (0);
}
