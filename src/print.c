/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:45:01 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/25 13:55:27 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_data *data, int id, char	*msg)
{
	pthread_mutex_lock(&data->print);
	if (!data->dead)
		printf("%lld %d %s\n", timestamp_ms() - data->start_time, id + 1, msg);
	pthread_mutex_unlock(&data->print);
}
