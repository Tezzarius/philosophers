/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:27:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/06 12:05:30 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->mutex_count)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = timestamp_ms();
	while (++i < data->philo_count)
		if (!create_philo(data, i))
			return (0);
	return (1);
}

static void	join_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->philo_count)
		pthread_join(data->philos[i++].thread, NULL);
}

static void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		data->philos[i++].last_meal = data->start_time;
	data->ready = 1;
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (parse_args(&data, ac, av) == 1)
		return (cleanup(&data), 1);
	if (init_forks(&data) || init_philos(&data))
		return (cleanup(&data), printf("Error: Init failed.\n"), 1);
	pthread_mutex_init(&data.lock, NULL);
	if (!create_threads(&data))
		return (cleanup(&data), 1);
	if (pthread_create(&monitor_thread, NULL, monitor, &data))
		return (cleanup(&data), 1);
	start_simulation(&data);
	join_threads(&data, monitor_thread);
	cleanup(&data);
	return (0);
}
