/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:52:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/03 15:53:18 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000LL) + (t.tv_usec / 1000LL));
}

void	print_status(t_philo *philo, char *msg)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_lock);
	if (!data->someone_dead)
		printf("%lld %d %s\n",
			timestamp_ms() - data->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(&data->print_lock);
}

void	smart_sleep(t_philo *philo, long long ms)
{
	long long	start;

	start = timestamp_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		if (philo->data->someone_dead)
		{
			pthread_mutex_unlock(&philo->data->print_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print_lock);
		if (timestamp_ms() - start >= ms)
			break ;
		usleep(500);
	}
}

int	create_thread(t_data *data, int i)
{
	data->philos[i].last_meal = data->start_time;
	data->philos[i].meals_eaten = 0;
	if ((data->philo_count) == 0 && pthread_create(data->philos[i].thread, NULL, routine_single, &data->philos[i]))
		pthread_join(data->philos[i].thread, NULL);
	else if ((data->philo_count % 2) == 0 && pthread_create(data->philos[i].thread, NULL, routine_even, &data->philos[i]))
	{
		while (i >= 0)
			pthread_join(data->philos[i--].thread, NULL);
		return (0);
	}
	else if (pthread_create(data->philos[i].thread, NULL, routine_odd, &data->philos[i]))
	{
		while (i >= 0)
			pthread_join(data->philos[i--].thread, NULL);
		return (0);
	}
	return (1);
}
