/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:27:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/05 13:45:34 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->lock);
	free(data->forks);
	free(data->philos);
}

static int	create_thread(t_data *data, int i)
{
	data->philos[i].last_meal = data->start_time;
	data->philos[i].meals_eaten = 0;
	if ((data->philo_count) == 1)
	{	
		if (pthread_create(&data->philos[i].thread, NULL, routine_single, &data->philos[i]))
			return (0);
	}
	else if ((data->philo_count % 2) == 0)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine_even, &data->philos[i]))
		{
			while (i >= 0)
				pthread_join(data->philos[i--].thread, NULL);
			return ((data->ready = -1), 0);
		}
	}
	else if (pthread_create(&data->philos[i].thread, NULL, routine_odd, &data->philos[i]))
	{
		while (i >= 0)
			pthread_join(data->philos[i--].thread, NULL);
		return ((data->ready = -1), 0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;
	pthread_t	monitor_thread;

	if (parse_args(&data, ac, av) == 1)
		return (1);
	if (init_forks(&data) || init_philos(&data))
		return (printf("Error: Init failed.\n"), 1);
	pthread_mutex_init(&data.lock, NULL);
	data.someone_dead = 0;
	data.start_time = timestamp_ms();
	i = -1;
	while (++i < data.philo_count)
		if (!create_thread(&data, i))
			return (0);
	if (pthread_create(&monitor_thread, NULL, monitor, &data))
		return (1);
	data.ready = 1;
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.philo_count)
		pthread_join(data.philos[i++].thread, NULL);
	cleanup(&data);
	return (0);
}
