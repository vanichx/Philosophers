/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:26:15 by ipetruni          #+#    #+#             */
/*   Updated: 2023/12/08 14:59:26 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_philo *philo)
{
	long int	t_now;

	pthread_mutex_lock(philo->params->print);
	t_now = time_now() - philo->meal;
	if (t_now >= philo->params->ttd)
	{
		pthread_mutex_unlock(philo->params->print);
		print_msg(philo, 5);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->params->print);
	return (0);
}

void	check_threads(t_philo *philo)
{
	int	i;

	while (!philo->params->ready)
		continue ;
	while (!philo->params->over)
	{
		i = -1;
		while (++i < philo->params->num_p)
		{
			if (check_death(&philo[i]))
				philo->params->over = 1;
		}
		if (philo->params->eated == philo->params->num_p)
			philo->params->over = 1;
	}
	return ;
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, 4);
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, 4);
	philo->meal = time_now();
	philo->iter++;
	print_msg(philo, 1);
	ft_usleep(philo->params->tte);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *phil)
{
	t_philo	*p;

	p = (t_philo *)phil;
	while (!(p->params->ready))
		continue ;
	if (p->id % 2 == 1)
		ft_usleep(p->params->tte * 0.9 + 1);
	while (!p->params->over)
	{
		eat(p);
		pthread_mutex_lock(p->params->print);
		if (p->params->check_tme && \
		p->iter == p->params->tme)
		{
			p->params->eated++;
			pthread_mutex_unlock(p->params->print);
			return (NULL);
		}
		pthread_mutex_unlock(p->params->print);
		print_msg(p, 2);
		ft_usleep(p->params->tts);
		print_msg(p, 3);
	}
	return (NULL);
}
