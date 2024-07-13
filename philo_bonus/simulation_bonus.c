/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:17:47 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:28:18 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_died(t_philo *philo)
{
	long	elapsed;
	int		time_to_die;

	elapsed = get_current_time() - get_long(philo->data->data_sem,
			&philo->last_meal);
	time_to_die = philo->data->time_to_die;
	if (elapsed > (long)time_to_die)
		return (1);
	return (0);
}

int	one_philo(t_philo *philo)
{
	philo->last_meal = get_current_time();
	philo->philo_pid = fork();
	if (philo->philo_pid == -1)
		return (write(2, "Error fork.\n", 12), 1);
	if (philo->philo_pid == 0)
	{
		print_status(philo, "has taken a fork\n");
		ft_usleep(philo->data->time_to_die, philo->data);
		print_status(philo, "died\n");
		exit(1);
	}
	return (0);
}

int	philo_full(t_philo *philo)
{
	if (philo->data->nbr_limit_meals != -1 && get_int(philo->data->data_sem,
			&philo->nbr_meals_eat) >= philo->data->nbr_limit_meals)
		return (1);
	return (0);
}

void	*main_check(void *philo_data)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_data;
	data = philo->data;
	while (1)
	{
		sem_wait(data->write_sem);
		if (philo_died(philo))
		{
			printf("%ld %d died\n", get_current_time() - data->start_time,
				philo->id);
			set_int(data->data_sem, &data->is_died, 1);
			exit(1);
		}
		sem_post(data->write_sem);
		if (philo_full(philo))
			break ;
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	if (data->nbr_philo == 1)
	{
		if (one_philo(&data->philos[0]))
			return (1);
	}
	else
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			data->philos[i].last_meal = get_current_time();
			data->philos[i].philo_pid = fork();
			if (data->philos[i].philo_pid == -1)
				return (write(2, "Error fork.\n", 12), 1);
			if (data->philos[i].philo_pid == 0)
				routine(&data->philos[i]);
		}
	}
	return (0);
}
