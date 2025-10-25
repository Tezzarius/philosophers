/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:27:27 by bschwarz          #+#    #+#             */
/*   Updated: 2025/10/25 14:23:49 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_tread_arg
{
	t_data *data;
	int		i;
}	t_thread_arg;

void	*thread_print(void *arg)
{
	t_thread_arg	*a;
	
	a = (t_thread_arg *)arg;
	print_status(a->data, a->i, "tot");
	free(a);
	return NULL;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	pthread_t	th[10];
	t_thread_arg	*arg;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(2, PHERROR "Wrong amount of arguments\n", 41), 1);
	if (init_data(&data, ac, av))
		return (write(2, PHERROR "Wrong input\n", 27), 1);
	smart_sleep(200);
	while (i < 10)
	{
		arg = malloc(sizeof(*arg));
		arg->data = &data;
		arg->i = i;
		pthread_create(&th[i], NULL, thread_print, arg);
		i++;	
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	return (0);
}
