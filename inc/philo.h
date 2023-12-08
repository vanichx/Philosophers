/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:06:24 by ipetruni          #+#    #+#             */
/*   Updated: 2023/12/08 11:13:11 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define FAINT "\033[2m"
# define RESET "\033[0m"
# define RED "\033[31m"
# define G "\033[32m"
# define B "\033[34m"
# define C "\033[36m"

typedef struct s_data
{
	int				tte;
	int				ttd;
	int				tts;
	int				tme;
	int				over;
	int				num_p;
	int				ready;
	int				check_tme;
	int				eated;
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				iter;
	long int		start;
	long int		meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_rork;
	t_data			*params;
}				t_philo;

/* parse.c */
int			check_input(char **argv);
t_data		*parse_data(char **argv);
void		init_philos(t_philo *philo, t_data *params);
int			check_value(char *arg, int min, int max, char *error_message);

/* routine.c */
int			check_death(t_philo *philo);
void		check_threads(t_philo *philo);
void		eat(t_philo *philo);
void		*routine(void *phil);

/* therads.c */
void		create_threads(t_philo *philo);
void		init_mutexes(t_philo *philo, t_data *params);
void		init_threads(t_philo *philo, t_data *params);
void		join_threads(t_philo *philo);

/* utils.c */
int			ft_atoi(const char *ptr);
u_int64_t	time_now(void);
void		ft_usleep(long int time);
void		print_msg(t_philo *philo, int i);
void		free_all(t_philo *philo);

#endif
