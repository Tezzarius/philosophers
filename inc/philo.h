/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:54:13 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/05 13:41:52 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                    INCLUDES                                */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                                    DEFINES                                 */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                    STRUCTS                                 */
/* ************************************************************************** */

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	pthread_mutex_t	lock;
	int				someone_dead;
	int				ready;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_data		*data;
	long long	last_meal;
	int			meals_eaten;
}	t_philo;

/* ************************************************************************** */
/*                                  PROTOTYPES                                */
/* ************************************************************************** */

int			parse_args(t_data *data, int ac, char **av);
void		*routine_even(void *arg);
void		*routine_odd(void *arg);
void		*routine_single(void *arg);
int			init_forks(t_data *data);
int			init_philos(t_data *data);
long		timestamp_ms(void);
void		print_status(t_philo *philo, char *msg);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		*monitor(void *arg);
void		smart_sleep(t_philo *philo, long long ms);

#endif