/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:52:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/25 13:59:52 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp_ms(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000LL) + (t.tv_usec / 1000LL);
}

void	smart_sleep(long long ms)
{
	long long	start = timestamp_ms();
	while ((timestamp_ms() - start) < ms)
		usleep(500);
}
