/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:06:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/03 11:33:47 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
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
		philo->meals_eaten++;
		smart_sleep(philo, philo->data->time_to_eat);
		drop_forks(philo);
		print_status(philo, "is sleeping");
		smart_sleep(philo, philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
