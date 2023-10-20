/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:47:55 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 18:03:44 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(PHILO_DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->philo_id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	messages(PHILO_TAKE_FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	messages(PHILO_TAKE_FORK, philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	messages(PHILO_EAT, philo);
	philo->meals_eaten++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	messages(PHILO_SLEEP, philo);
	ft_usleep(philo->data->sleep_time);
}
