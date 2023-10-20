/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:50:27 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 14:20:42 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	memory_allocation(t_data *data)
{
	data->th_id = malloc(sizeof(pthread_t) * data->number_of_philo);
	if (data->th_id == NULL)
		return (error(MERROR_1, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (data->forks == NULL)
		return (error(MERROR_2, data));
	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (data->philos == NULL)
		return (error(MERROR_3, data));
	return (0);
}

void	free_data(t_data *data)
{
	if (data->th_id)
		free(data->th_id);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free_data(data);
}
