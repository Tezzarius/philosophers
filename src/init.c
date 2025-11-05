/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:50:37 by bschwarz          #+#    #+#             */
/*   Updated: 2025/11/05 14:38:18 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_atoi(const char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i] - '0');
	return (res);
}

static int	valid_digit(char *s)
{
	int	i;

	if (!*s)
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] < '0' || s[i] > '9')
			return (0);
	return (1);
}

int	parse_args(t_data *data, int ac, char **av)
{
	int	i;

	memset(data, 0, sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (printf("Usage: philos, die, eat, sleep, must_eat(opt)"), 1);
	i = 0;
	while (++i < ac)
		if (!valid_digit(av[i]))
			return (printf("Error: Non-numeric argument detected.\n"), 1);
	data->philo_count = philo_atoi(av[1]);
	data->time_to_die = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = philo_atoi(av[5]);
	if (data->philo_count < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (printf("Error: Values must be greater than 0.\n"), 1);
	return (0);
}
