/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:06:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/08 16:21:56 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_to_do(t_philo *philo)
{
	int	done;

	take_forks(philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = timestamp_ms();
	pthread_mutex_unlock(&philo->data->lock);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->meals_eaten++;
	done = (philo->meals_eaten == philo->data->must_eat);
	pthread_mutex_unlock(&philo->data->lock);
	smart_sleep(philo, philo->data->time_to_eat);
	drop_forks(philo);
	if (done)
		return (0);
	print_status(philo, "is sleeping");
	smart_sleep(philo, philo->data->time_to_sleep);
	print_status(philo, "is thinking");
	return (1);
}

static void	*routine_even(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!wait_until_ready(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (is_stopped(philo))
			break ;
		if (!philo_to_do(philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static void	*routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!wait_until_ready(philo))
		return (NULL);
	if (philo->id == 0 || philo->id % 2 == 1)
		smart_sleep(philo, philo->data->time_to_eat);
	while (1)
	{
		if (is_stopped(philo))
			break ;
		if (!philo_to_do(philo))
			return (NULL);
		smart_sleep(philo, philo->data->time_to_eat + 1);
	}
	return (NULL);
}

void	*routine_single(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	smart_sleep(philo, philo->data->time_to_die);
	print_status(philo, "died");
	return (NULL);
}

int	create_philo(t_data *data, int i)
{
	data->philos[i].meals_eaten = 0;
	if ((data->philo_count % 2) == 0)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine_even, &data->philos[i]))
		{
			while (i >= 0)
				pthread_join(data->philos[i--].thread, NULL);
			return ((data->ready = -1), 0);
		}
	}
	else if (pthread_create(&data->philos[i].thread, NULL,
			routine_odd, &data->philos[i]))
	{
		while (i >= 0)
			pthread_join(data->philos[i--].thread, NULL);
		data->ready = -1;
		return (0);
	}
	return (1);
}
