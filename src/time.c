/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:14:27 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 14:02:08 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

int	ft_usleep(useconds_t sleep_time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(sleep_time / 10);
	return (0);
}
