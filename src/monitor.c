/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:03:34 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/05 14:44:31 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_full(t_data *data)
{
	int	i;

	if (data->must_eat == -1)
		return (0);
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->lock);
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			pthread_mutex_unlock(&data->lock);
			return (0);
		}
		pthread_mutex_unlock(&data->lock);
	}
	return (1);
}

static void	kill_philo(t_data *data, int i)
{
	data->someone_dead = 1;
	printf("%ld %d died\n", timestamp_ms() - data->start_time,
		data->philos[i].id + 1);
	pthread_mutex_unlock(&data->lock);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->someone_dead)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_lock(&data->lock);
			if ((timestamp_ms() - data->philos[i].last_meal)
				> data->time_to_die)
				return (kill_philo(data, i), NULL);
			pthread_mutex_unlock(&data->lock);
		}
		if (check_all_full(data))
		{
			pthread_mutex_lock(&data->lock);
			data->someone_dead = 1;
			pthread_mutex_unlock(&data->lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
