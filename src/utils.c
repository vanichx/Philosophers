/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:47:55 by ipetruni          #+#    #+#             */
/*   Updated: 2023/12/08 14:51:47 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *ptr)
{
	int	sign;
	int	i;
	int	sum;

	sum = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ptr[i] != '\0' && ptr[i] >= '0' && ptr[i] <= '9')
	{
		sum *= 10;
		sum += ptr[i] - '0';
		i++;
	}
	sum *= sign;
	return (sum);
}

u_int64_t	time_now(void)
{
	uint64_t		milliseconds;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(long int time)
{
	long int	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < (unsigned long long) time)
		usleep(150);
}

void	print_msg(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->params->print);
	if (philo->params->over)
	{
		pthread_mutex_unlock(philo->params->print);
		return ;
	}
	if (i == 1)
		printf(G"%llu %d is eating\n"RESET, \
			time_now() - philo->start, philo->id);
	else if (i == 2)
		printf(C"%llu %d is sleeping\n"RESET, \
			time_now() - philo->start, philo->id);
	else if (i == 3)
		printf(B"%llu %d is thinking\n"RESET, \
			time_now() - philo->start, philo->id);
	else if (i == 4)
		printf(FAINT"%llu %d has taken fork\n"RESET, \
			time_now() - philo->start, philo->id);
	else if (i == 5)
		printf(RED"%llu %d died\n"RESET, \
			time_now() - philo->start, philo->id);
	pthread_mutex_unlock(philo->params->print);
}

void	free_all(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->params->num_p)
		pthread_mutex_destroy(philo[i].left_fork);
	pthread_mutex_destroy(philo->params->print);
	free(philo->params->print);
	free(philo->params->fork);
	free(philo->params);
	free(philo);
}
