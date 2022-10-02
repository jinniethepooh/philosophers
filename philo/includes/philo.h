/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:48:33 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/03 02:46:57 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# include "philo_colour.h"

typedef struct timeval	t_timeval;

typedef struct s_time
{
	long	die;
	long	eat;
	long	sleep;
	int		n_eat;
}	t_time;

typedef struct s_end
{
	int				limit_counter;
	int				found;
	pthread_mutex_t	dead_lock;
}	t_end;

typedef struct s_info
{
	int			n_philo;
	t_time		time_to;
}	t_info;

typedef struct s_philo
{
	t_info			info;
	t_end			*end;
	t_timeval		kickoff;
	t_timeval		hp;
	int				s_philo;
	int				n_ate;
	int				l_fork;
	int				r_fork;
	pthread_t		life;
	pthread_mutex_t	*used_fork;
}	t_philo;

// - checker - //
int		ft_isspace(char c);
int		ft_isdigit(char c);
int		is_validinput(int ac, char **av);

// - error handler - //
void	*malloc_error(void);
void	*thread_init_error(void);
int		error_input(void);

// - helper - //
int		ft_atoi(const char *str);
int		get_timestamp(t_timeval now, t_timeval then);
int		still_alive(t_timeval now, t_philo *philo);
void	print_log(int s_philo, long timestamp, const char *act);

// - free - //
void	free_at_exit(t_philo **philo);

// - initiator - //
void	philo_init(t_philo **philo, int n_philo, int argc, char **argv);

// - circle of life - //
void	*life_cycle(void *philo_addr);

// - life w/ forks - //
void	look_for_forks(t_philo *philo, int *fork, char side);
void	put_forks_back(t_philo *philo);

#endif
