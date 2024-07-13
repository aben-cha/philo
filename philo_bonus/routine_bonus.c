/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:17:56 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:23:11 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pthread_create(&(philo->monitor_thread), NULL, main_check, philo))
		exit (1);
	if (philo->id % 2)
		ft_usleep(60, data);
	while (!get_int(data->data_sem, &data->is_died))
	{
		eating(philo);
		if (philo_full(philo))
			break ;
		sleeping(philo);
		thinking(philo);
	}
	if (pthread_join(philo->monitor_thread, NULL))
		exit(1);
	exit(0);
}

void	print_status(t_philo *philo, char *string)
{
	size_t	start_time;

	sem_wait(philo->data->data_sem);
	start_time = philo->data->start_time;
	sem_post(philo->data->data_sem);
	sem_wait(philo->data->write_sem);
	if (!get_int(philo->data->data_sem, &philo->data->is_died))
		printf("%ld %d %s", get_current_time() - start_time,
			philo->id, string);
	sem_post(philo->data->write_sem);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork\n");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork\n");
	sem_wait(philo->data->data_sem);
	philo->last_meal = get_current_time();
	philo->nbr_meals_eat++;
	sem_post(philo->data->data_sem);
	print_status(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat, philo->data);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
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
