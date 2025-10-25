/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:27:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/25 12:29:38 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// long long	timestamp_ms(void)
// {
// 	struct timeval t;
// 	gettimeofday(&t, NULL);
// 	return (t.tv_sec * 1000LL) + (t.tv_usec / 1000LL);
// }

// void	smart_sleep(long long ms)
// {
// 	long long	start = timestamp_ms();
// 	while ((timestamp_ms() - start) < ms)
// 		usleep(500);
// }

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (write(2, PHERROR "Wrong amount of arguments\n", 41), 1);
	if (init_data(&data, ac, av))
		return (write(2, PHERROR "Wrong input\n", 27), 1);
	(void)ac;
	(void)av;
	return (0);
}
