/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:26:15 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 16:16:22 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philos[i].data = data;
		data->philos[i].philo_id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philos[i].left_fork = &data->forks[0];
	data->philos[i].right_fork = &data->forks[data->number_of_philo - 1];
	i = 1;
	while (i < data->number_of_philo)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->number_of_philo = (int) ft_atoi(argv[1]);
	data->death_time = (u_int64_t) ft_atoi(argv[2]);
	data->eat_time = (u_int64_t) ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_meals = (int) ft_atoi(argv[5]);
	else
		data->number_of_meals = -1;
	if (data->number_of_philo <= 0 || data->number_of_philo > 200
		|| data->death_time < 0 || data->eat_time < 0 || data->sleep_time < 0)
		return (error(INV_VALUES, NULL));
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	init(int argc, char **argv, t_data *data)
{
	if (init_data(argc, argv, data))
		return (1);
	if (memory_allocation(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philos(data);
	return (0);
}
