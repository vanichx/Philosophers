/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:06:24 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/10 16:18:27 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* memset */
# include <string.h>

/* printf */
# include <stdio.h>

/* malloc and free */
# include <stdlib.h>

/* write and usleep */
# include <unistd.h>

/* gettimeofday */
# include <sys/time.h>

/*  pthread functions (pthread_create, etc.) */
# include <pthread.h>

/* bool */
# include <stdbool.h>

/* Some Error Definitions */
# define PHILO_DIED "died"
# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_TAKE_FORK "has taken a fork"
# define MERROR_2 "Failed while mallocing Forks"
# define MERROR_3 "Failed while mallocing Philos"
# define JOIN_ERROR "Error while joining threads"
# define THREAD_ERROR_1 "Error while creating threads"
# define MERROR_1 "Failed while mallocing Threads IDs"
# define INV_VALUES "Program params has some invalid values"
# define INV_CHARACTERS "Some of parametrs should be digits only"

/* a structure to represent a philosopher */
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		th;
	int				philo_id;
	int				meals_eaten;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

/* a structure to represent all usefull data */
typedef struct s_data
{
	pthread_t		*th_id;
	int				number_of_philo;
	int				number_of_meals;
	int				dead;
	int				finished;
	t_philo			*philos;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		death_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}				t_data;

/* life.c */
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		messages(char *str, t_philo *philo);

/* threads.c */
int			init_threads(t_data *data);
void		*monitor(void *data_pointer);
void		*routine(void *philo_pointer);

/* init.c */
int			init_forks(t_data *data);
int			init(int argc, char **argv, t_data *data);
void		init_philos(t_data *data);
int			init_data(int argc, char **argv, t_data *data);

/* error.c */

/* args_checks.c */
int			ft_atoi(const char *str);
int			args_checks(char **argv);
int			ft_strcmp(const char *s1, const char *s2);

/* malloc.c */
void		ft_exit(t_data *data);
void		free_data(t_data *data);
int			error(char *str, t_data *data);
int			memory_allocation(t_data *data);

/* time.c */
u_int64_t	get_time(void);
int			ft_usleep(useconds_t sleep_time);

#endif
