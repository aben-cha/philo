/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:21:55 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 00:35:56 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->id % 2 == 0)
		ft_usleep(60, philo->data);
	while (!get_int(&philo->data->data_mutex, &philo->data->is_died)
		&& !get_int(&philo->data->data_mutex, &philo->data->full_data))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *string)
{
	long	start_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	start_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!get_int(&philo->data->data_mutex, &philo->data->is_died)
		&& !get_int(&philo->data->data_mutex, &philo->data->full_data))
		printf("%ld %d %s", get_current_time() - start_time, philo->id, string);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal = get_current_time();
	philo->nbr_meals_eat++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_status(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking\n");
}
