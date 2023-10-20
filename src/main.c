/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:28:50 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 16:12:38 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->th_id[0], NULL, &routine, &data->philos[0]))
		return (error(THREAD_ERROR_1, data));
	pthread_detach(data->th_id[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (args_checks(argv))
		return (1);
	if (init(argc, argv, &data))
		return (1);
	if (data.number_of_philo == 1)
		return (case_one(&data));
	if (init_threads(&data))
		return (0);
	ft_exit(&data);
	return (0);
}
