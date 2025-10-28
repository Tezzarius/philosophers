/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:27:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/28 21:15:10 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_lock);
	free(data->forks);
	free(data->philos);
}

// Debug
//
// static void	print_data(t_data *data)
// {
// 	printf("philos: %d\ndie: %d\neat: %d\nsleep: %d\nmust_eat: %d\n",
// 		data->philo_count, data->time_to_die, data->time_to_eat,
// 		data->time_to_sleep, data->must_eat);
// }

int	main(int ac, char **av)
{
	t_data		data;
	int			i;
	pthread_t	monitor_thread;

	if (parse_args(&data, ac, av) == 1)
		return (1);
	if (init_forks(&data) || init_philos(&data))
		return (printf("Error: Init failed.\n"), 1);
	pthread_mutex_init(&data.print_lock, NULL);
	data.someone_dead = 0;
	data.start_time = timestamp_ms();
	i = -1;
	while (++i < data.philo_count)
	{
		data.philos[i].last_meal = data.start_time;
		data.philos[i].meals_eaten = 0;
		pthread_create(&data.philos[i].thread,
			NULL, philo_routine, &data.philos[i]);
	}
	pthread_create(&monitor_thread, NULL, monitor, &data);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.philo_count)
		pthread_join(data.philos[i++].thread, NULL);
	cleanup(&data);
	return (0);	
}
