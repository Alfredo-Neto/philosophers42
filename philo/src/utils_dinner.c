/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:11:23 by ade-agui          #+#    #+#             */
/*   Updated: 2022/09/04 12:37:55 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->struct_data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->struct_data->meal);
	philo->last_dinner = get_time();
	pthread_mutex_unlock(&philo->struct_data->meal);
	print_status(get_time(), philo, "has taken a fork 🍽️");
	pthread_mutex_unlock(&philo->struct_data->forks[philo->left_fork]);
	print_status(get_time(), philo, "DIED 💀");
	pthread_mutex_lock(&philo->struct_data->m_checker);
	philo->struct_data->checker = 1;
	pthread_mutex_unlock(&philo->struct_data->m_checker);
	return (NULL);
}

void	eat(t_philo *philo)
{
	mutex_lock_fork(philo);
	pthread_mutex_lock(&philo->struct_data->meal);
	philo->eating = 1;
	philo->last_dinner = get_time();
	pthread_mutex_unlock(&philo->struct_data->meal);
	print_status(get_time(), philo, "has taken a fork 🍽️");
	print_status(get_time(), philo, "has taken a fork 🍽️");
	print_status(get_time(), philo, "is eating 🍕");
	usleep(philo->struct_data->time_to_eat);
	pthread_mutex_lock(&philo->struct_data->meal);
	philo->had_dinner++;
	pthread_mutex_unlock(&philo->struct_data->meal);
	mutex_unlock_fork(philo);
}

void	*died(void *param)
{
	int		i;
	t_data	*data;

	data = param;
	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_lock(&data->meal);
		if (is_a_dead_philo(data, i))
			return (NULL);
		if (data->philo[i].had_dinner == data->to_dinner
			&& data->to_dinner > 0 && data->philo[i].eating)
		{
			data->ate_dinner++;
			data->philo[i].eating = 0;
		}
		pthread_mutex_unlock(&data->meal);
		if (all_philo_satisfied(data))
			return (NULL);
		if (i + 1 == data->number_of_philos)
			i = -1;
		usleep (1000);
	}
	return (NULL);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->struct_data->number_of_philos == 1)
		return (one_philo(philo));
	while (true)
	{
		if (philo->philo_id % 2 == 0)
			usleep(1000);
		eat(philo);
		print_status(get_time(), philo, "is sleeping 😴");
		usleep(philo->struct_data->time_to_sleep);
		print_status(get_time(), philo, "is thinking 🤔");
		pthread_mutex_lock(&philo->struct_data->m_checker);
		if (philo->struct_data->checker == 1)
		{
			pthread_mutex_unlock(&philo->struct_data->m_checker);
			break ;
		}
		pthread_mutex_unlock(&philo->struct_data->m_checker);
	}
	return (NULL);
}
