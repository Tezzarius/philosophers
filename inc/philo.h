/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:54:13 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/25 13:53:57 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                    INCLUDES                                */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                                    DEFINES                                 */
/* ************************************************************************** */

# define PHERROR "philo: error: "

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
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t print;
	int				dead;
	// t_philo			*philos;
}	t_data;

typedef	struct s_philo
{
	int			id;
	int			meals;
	long long	last_meal;
	pthread_t	thread;
	t_data		*data;	
}	t_philo;

/* ************************************************************************** */
/*                                  PROTOTYPES                                */
/* ************************************************************************** */

int			init_data(t_data *data, int ac, char **av);
int			ft_atoi(const char *nptr);
long long	timestamp_ms(void);
void		smart_sleep(long long ms);
void		print_status(t_data *data, int id, char	*msg);

#endif