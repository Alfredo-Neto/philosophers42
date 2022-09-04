/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:10:52 by ade-agui          #+#    #+#             */
/*   Updated: 2022/09/04 12:37:55 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(long int time_now, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->struct_data->print);
	pthread_mutex_lock(&philo->struct_data->m_checker);
	if (philo->struct_data->checker != 1)
		printf("Time:%6ld | Philo:%3d |Status: %s\n",
			time_now - philo->struct_data->start_dinner,
			philo->philo_id, status);
	pthread_mutex_unlock(&philo->struct_data->m_checker);
	pthread_mutex_unlock(&philo->struct_data->print);
}

int	is_a_dead_philo(t_data *data, int i)
{
	if (get_time() - data->philo[i].last_dinner > data->time_to_die)
	{
		print_status(get_time(), data->philo + i, "DIED 💀");
		pthread_mutex_lock(&data->m_checker);
		data->checker = 1;
		pthread_mutex_unlock(&data->m_checker);
		pthread_mutex_unlock(&data->meal);
		return (1);
	}
	return (0);
}

int	all_philo_satisfied(t_data *data)
{
	if (data->ate_dinner == data->number_of_philos)
	{
		pthread_mutex_lock(&data->m_checker);
		data->checker = 1;
		pthread_mutex_unlock(&data->m_checker);
		return (1);
	}
	return (0);
}
