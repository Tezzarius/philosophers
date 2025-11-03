/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:52:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/03 11:28:52 by bschwarz         ###   ########.fr       */
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
	while (!philo->data->someone_dead)
	{
		if (timestamp_ms() - start >= ms)
			break ;
		usleep(500);
	}
}
