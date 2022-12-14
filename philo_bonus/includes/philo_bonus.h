/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:48:33 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 16:12:56 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# include "philo_colour.h"

typedef struct timeval	t_timeval;

typedef struct s_time
{
	unsigned long	die;
	unsigned long	eat;
	unsigned long	sleep;
	int				n_eat;
}	t_time;

typedef struct s_info
{
	int		n_philo;
	t_time	time_to;
}	t_info;

typedef struct s_semaphore
{
	sem_t	*dead;
	sem_t	*end;
	sem_t	*forks;
	sem_t	*limit;
}	t_semaphore;

typedef struct s_philo
{
	int			s_philo;
	int			n_ate;
	t_info		info;
	t_timeval	kickoff;
	t_timeval	hp;
	sem_t		*dead;
	sem_t		*end;
	sem_t		*forks;
	sem_t		*limit;
}	t_philo;

// - checker - //
int				ft_isspace(char c);
int				ft_isdigit(char c);
int				is_validinput(int ac, char **av);
int				still_alive(t_timeval now, t_philo *philo);

// - error handler - //
int				input_error(void);

// - helper - //
int				ft_atoi(const char *str);
void			adj_usleep(unsigned long time_to_ms);
void			print_log(int s_philo, unsigned long timestamp, \
					const char *act);
t_timeval		get_now(void);
unsigned long	get_timestamp(t_timeval now, t_timeval then);

// - free - //
int				free_at_exit(t_philo **philo, int *f_pid, int exit_code);

// - initiator - //
int				philo_init(t_philo **philo, int n_philo, int argc, char **argv);

// - circle of life - //
int				life_cycle(t_philo *philo);
int				limit_tracker_init(t_philo *philo, int time_to_eat);
int				hp_tracker_init(t_philo *philo);
void			*limit_tracker(void *philo_addr);
void			*hp_tracker(void *philo_addr);

// - life w/ forks - //
void			look_for_forks(t_philo *philo);
void			put_forks_back(t_philo *philo);

#endif
