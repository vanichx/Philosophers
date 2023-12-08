/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:57:46 by ipetruni          #+#    #+#             */
/*   Updated: 2023/12/08 14:48:32 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	create_threads(t_philo *philo)
{
	int			i;
	long int	time;

	i = -1;
	while (++i < philo->params->num_p)
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
	i = -1;
	time = time_now();
	while (++i < philo->params->num_p)
	{
		philo[i].start = time;
		philo[i].meal = time;
	}
	philo->params->ready = 1;
}

void	init_mutexes(t_philo *philo, t_data *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
		pthread_mutex_init(philo[i].left_fork, NULL);
	pthread_mutex_init(params->print, NULL);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->params->num_p)
		pthread_join(philo[i].thread, (void *)&philo[i]);
}

void	init_threads(t_philo *philo, t_data *params)
{
	init_mutexes(philo, params);
	create_threads(philo);
	check_threads(philo);
}
