/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:52:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/08 16:14:12 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *msg)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (!data->someone_dead)
		printf("%ld %d %s\n",
			timestamp_ms() - data->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(&data->lock);
}

void	smart_sleep(t_philo *philo, long long ms)
{
	long long	start;

	start = timestamp_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->someone_dead)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (timestamp_ms() - start >= ms)
			break ;
		usleep(500);
	}
}

int	wait_until_ready(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->ready == -1)
			return (pthread_mutex_unlock(&philo->data->lock), 0);
		if (philo->data->ready == 1)
			return (pthread_mutex_unlock(&philo->data->lock), 1);
		pthread_mutex_unlock(&philo->data->lock);
		usleep(100);
	}
}

int	is_stopped(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->data->lock);
	stopped = philo->data->someone_dead;
	pthread_mutex_unlock(&philo->data->lock);
	return (stopped);
}
