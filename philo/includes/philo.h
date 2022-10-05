/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:48:33 by cchetana          #+#    #+#             */
/*   Updated: 2022/10/05 15:52:18 by cchetana         ###   ########.fr       */
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
	unsigned long	die;
	unsigned long	eat;
	unsigned long	sleep;
	int				n_eat;
}	t_time;

typedef struct s_end
{
	int	limit_counter;
	int	found;
}	t_end;

typedef struct s_info
{
	int		n_philo;
	t_time	time_to;
}	t_info;

typedef struct s_philo
{
	int				s_philo;
	int				n_ate;
	t_end			*end;
	t_info			info;
	t_timeval		kickoff;
	t_timeval		hp;
	pthread_t		life;
	pthread_mutex_t	log;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*used_fork;
}	t_philo;

// - checker - //
int				ft_isspace(char c);
int				ft_isdigit(char c);
int				is_validinput(int ac, char **av);
int				still_alive(t_timeval now, t_philo *philo);

// - error handler - //
int				input_error(void);
int				malloc_error(void);
int				thread_init_error(void);

// - helper - //
int				ft_atoi(const char *str);
void			adj_usleep(unsigned long time_to_ms);
void			print_log(int s_philo, unsigned long timestamp, \
					const char *act);
t_timeval		get_now(void);
unsigned long	get_timestamp(t_timeval now, t_timeval then);

// - free - //
void			free_at_exit(t_philo *philo);

// - initiator - //
int				philo_init(t_philo *philo, t_philo philo_tmp, int n_philo);

// - circle of life - //
void			*life_cycle(void *philo_addr);
void			*hp_tracker(void *philo_addr);

// - life w/ forks - //
int				assign_forks(t_philo *philo, int n_philo);
void			look_for_forks(t_philo *philo);
void			put_forks_back(t_philo *philo);

#endif
