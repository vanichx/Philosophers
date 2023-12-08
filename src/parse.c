/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:43:37 by ipetruni          #+#    #+#             */
/*   Updated: 2023/12/08 11:12:06 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	arg_is_number(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			printf(RED"Error: arguments must be numbers\n"RESET);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_value(char *arg, int min, int max, char *error_message)
{
	int	value;

	value = ft_atoi(arg);
	if (value < min || value > max)
	{
		printf(RED"%s\n"RESET, error_message);
		return (0);
	}
	return (1);
}

int	check_input(char **argv)
{
	if (!arg_is_number(argv[1]) || !check_value(argv[1], 1, 200, \
		"Error: number of philosophers must be at this limits (1 to 200)"))
		return (0);
	if (!arg_is_number(argv[2]) || !check_value(argv[2], 60, INT_MAX, \
		"Error: time to die must be at least 60 ms"))
		return (0);
	if (!arg_is_number(argv[3]) || !check_value(argv[3], 60, INT_MAX, \
		"Error: time to eat must be at least 60 ms"))
		return (0);
	if (!arg_is_number(argv[4]) || !check_value(argv[4], 60, INT_MAX, \
		"Error: time to sleep must be at least 60 ms"))
		return (0);
	if (argv[5] && (!arg_is_number(argv[5]) \
		|| !check_value(argv[5], 1, INT_MAX, \
		"Error: number of times each philosopher \
		must eat must be greater than 0")))
		return (0);
	return (1);
}

t_data	*parse_data(char **argv)
{
	t_data	*params;

	params = malloc(sizeof(t_data));
	if (!params)
		return (NULL);
	params->print = malloc(sizeof(pthread_mutex_t));
	if (!params->print)
		return (NULL);
	params->fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!params->fork)
		return (NULL);
	params->num_p = ft_atoi(argv[1]);
	params->ttd = ft_atoi(argv[2]);
	params->tte = ft_atoi(argv[3]);
	params->tts = ft_atoi(argv[4]);
	params->check_tme = 0;
	params->eated = 0;
	if (argv[5])
	{
		params->check_tme = 1;
		params->tme = ft_atoi(argv[5]);
	}
	params->ready = 0;
	params->over = 0;
	return (params);
}

void	init_philos(t_philo *philo, t_data *params)
{
	int	i;

	i = -1;
	while (++i < params->num_p)
	{
		philo[i].start = 0;
		philo[i].id = i + 1;
		philo[i].thread = 0;
		philo[i].meal = 0;
		philo[i].left_fork = &params->fork[i];
		if (philo[i].id == params->num_p)
			philo[i].right_rork = &params->fork[0];
		else
			philo[i].right_rork = &params->fork[i + 1];
		philo[i].params = params;
		philo[i].iter = 0;
	}
}
