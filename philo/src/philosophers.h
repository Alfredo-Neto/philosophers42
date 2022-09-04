/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:11:10 by ade-agui          #+#    #+#             */
/*   Updated: 2022/09/04 12:37:55 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define MIN_ARGS	5
# define MAX_ARGS	6

//error messages
# define USAGE "Usage: ./philo philo_id ms_to_die ms_eat ms_sleep [have_to_eat]"
# define NOT_UNINT "Arguments must be integers greater than 0"
# define PTHREAD_FAILURE "Could not create thread"
# define JOIN_FAILURE "Could not join thread"

typedef struct s_data		t_data;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				philo_id;
	int				had_dinner;
	long int		last_dinner;
	bool			eating;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	t_data			*struct_data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_dinner;
	int				checker;
	int				ate_dinner;
	long int		start_dinner;
	t_philo			*philo;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	m_checker;
	pthread_mutex_t	print;
}				t_data;

//error_check.c
bool		error_check(int argc, char **argv);
bool		error(char *message);

//mutex.c
void		init_mutex(t_data *data);
void		destroy_mutex(t_data *data);
void		mutex_lock_fork(t_philo *philo);
void		mutex_unlock_fork(t_philo *philo);

//philo_status.c
void		print_status(long int time_now, t_philo *philo, char *status);
int			is_a_dead_philo(t_data *data, int i);
int			all_philo_satisfied(t_data *data);
//utils_dinner.c
void		*routine(void *param);
void		*died(void *param);
void		*one_philo(t_philo *philo);
void		eat(t_philo *philo);

//utils.c
int			ft_isdigit(int c);
int			ft_atoi(const char *ptr);
double		philos_atoi(const char *ptr);
long int	get_time(void);
void		ft_bzero(void *s, size_t n);

#endif