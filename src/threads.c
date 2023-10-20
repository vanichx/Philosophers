/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:57:46 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 16:12:12 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->number_of_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			messages(PHILO_DIED, philo);
		if (philo->meals_eaten == philo->data->number_of_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->meals_eaten++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->th, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		messages(PHILO_THINK, philo);
	}
	if (pthread_join(philo->th, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	th;

	i = -1;
	data->start_time = get_time();
	if (data->number_of_meals > 0)
	{
		if (pthread_create(&th, NULL, &monitor, &data->philos[0]))
			return (error(THREAD_ERROR_1, data));
	}
	while (++i < data->number_of_philo)
	{
		if (pthread_create(&data->th_id[i], NULL, &routine, &data->philos[i]))
			return (error(THREAD_ERROR_1, data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->number_of_philo)
	{
		if (pthread_join(data->th_id[i], NULL))
			return (error(JOIN_ERROR, data));
	}
	return (0);
}
