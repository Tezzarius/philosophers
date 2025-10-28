/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:43:45 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/28 20:57:23 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->philo_count;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	int left;
	int right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->philo_count;
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);	
}
