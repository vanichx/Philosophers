/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:28:50 by ipetruni          #+#    #+#             */
/*   Updated: 2023/12/07 17:24:49 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



int main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	if (argc == 5 || argc == 6)
	{
		if (!check_input(argv))
			return (0);
		philos = malloc (sizeof(t_philo) * ft_atoi(argv[1]));
		data = parse_data(argv);
		init_philos(philos, data);
		init_threads(philos, data);
		join_threads(philos);
		free_all(philos);
	}
	else
	{
		printf(RED"Error: Invalid number of arguments\n"RESET);
		printf(G"Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number of meals]\n"RESET);
		printf(G"Optional: [number of meals]\n"RESET);
		printf(G"Example: ./philo 5 800 200 200 7\n"RESET);
	}
	return (0);
}