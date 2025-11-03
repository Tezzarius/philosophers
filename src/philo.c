/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:06:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/03 14:43:56 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_even(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_dead)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->data->print_lock);
		philo->last_meal = timestamp_ms();
		pthread_mutex_unlock(&philo->data->print_lock);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->data->print_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->print_lock);
		smart_sleep(philo, philo->data->time_to_eat);
		drop_forks(philo);
		if (philo->meals_eaten == philo->data->must_eat)
			return (NULL);
		print_status(philo, "is sleeping");
		smart_sleep(philo, philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id == 0 || philo->id % 2 == 1)
		smart_sleep(philo, philo->data->time_to_eat);
	while (!philo->data->someone_dead)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->data->print_lock);
		philo->last_meal = timestamp_ms();
		pthread_mutex_unlock(&philo->data->print_lock);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->data->print_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->print_lock);
		smart_sleep(philo, philo->data->time_to_eat);
		drop_forks(philo);
		if (philo->meals_eaten == philo->data->must_eat)
			return (NULL);
		print_status(philo, "is sleeping");
		smart_sleep(philo, philo->data->time_to_sleep);
		print_status(philo, "is thinking");
		smart_sleep(philo, philo->data->time_to_eat);
		usleep(1000);
	}
	return (NULL);
}

void	*routine_single(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	print_status(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	return (NULL);
}
