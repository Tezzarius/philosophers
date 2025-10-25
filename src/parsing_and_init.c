/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:50:37 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/25 13:40:26 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	neg;
	size_t	dest;

	i = 0;
	neg = 1;
	dest = 0;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		dest = dest * 10;
		dest = dest + (nptr[i] - '0');
		i++;
	}
	return (dest * neg);
}

int init_data(t_data *data, int ac, char **av)
{
	if ((data->philo_count = ft_atoi(av[1])) < 1)
		return 1;
	if ((data->time_to_die = ft_atoi(av[2])) < 1)
		return 1;
	if ((data->time_to_eat = ft_atoi(av[3])) < 1)
		return 1;
	if ((data->time_to_sleep = ft_atoi(av[4])) < 1)
		return 1;
	if (ac == 6)
	{
		if ((data->must_eat = ft_atoi(av[5])) < 1)
			return 1;
	}
	else
		data->must_eat = -1;
	data->start_time = 0;
	data->forks = NULL;
	// data->print = NULL;
	data->dead = 0;
	return 0;
}
