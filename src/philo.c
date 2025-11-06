/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:06:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/06 11:59:29 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_to_do(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = timestamp_ms();
	pthread_mutex_unlock(&philo->data->lock);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->lock);
	smart_sleep(philo, philo->data->time_to_eat);
	drop_forks(philo);
	if (philo->meals_eaten == philo->data->must_eat)
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
	while (1)
	{
		if (philo->data->ready == 1)
			break ;
		else if (philo->data->ready == -1)
			return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_dead)
		if (!philo_to_do(philo))
			return (NULL);
	return (NULL);
}

static void	*routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->ready == 1)
			break ;
		else if (philo->data->ready == -1)
			return (NULL);
	}
	if (philo->id == 0 || philo->id % 2 == 1)
		smart_sleep(philo, philo->data->time_to_eat);
	while (!philo->data->someone_dead)
	{
		if (!philo_to_do(philo))
			return (NULL);
		smart_sleep(philo, philo->data->time_to_eat + 1);
	}
	return (NULL);
}

static void	*routine_single(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	print_status(philo, "has taken a fork");
	while (!philo->data->someone_dead)
	{
		usleep(1000);
		if ((timestamp_ms() - philo->last_meal) > philo->data->time_to_die)
			break;
	}
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	return (NULL);
}

int	create_philo(t_data *data, int i)
{
	data->philos[i].meals_eaten = 0;
	if ((data->philo_count) == 1)
		if (pthread_create(&data->philos[0].thread, NULL,
				routine_single, &data->philos[0]))
			return (0);
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
		return ((data->ready = -1), 0);
	}
	return (1);
}
