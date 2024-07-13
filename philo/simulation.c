/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:11:39 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/25 09:33:23 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	elapsed = get_current_time()
		- get_long(&philo->data->data_mutex, &philo->last_meal);
	time_to_die = (long)(philo->data->time_to_die);
	if (elapsed > time_to_die)
		return (1);
	return (0);
}

int	philo_full(t_data *data)
{
	int	i;

	i = 0;
	while (data->nbr_limit_meals != -1 && i < data->nbr_philo
		&& get_int(&data->data_mutex,
			&data->philos[i].nbr_meals_eat) >= data->nbr_limit_meals)
		i++;
	if (i == data->nbr_philo)
	{
		set_int(&data->data_mutex, &data->full_data, 1);
		return (1);
	}
	return (0);
}

void	main_thread_check(t_data *data)
{
	int	i;

	while (!get_int(&data->data_mutex, &data->full_data))
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->write_mutex);
			if (philo_died(&data->philos[i]))
			{
				if (!get_int(&data->data_mutex, &data->is_died))
					printf("%ld %d died\n", get_current_time()
						- data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->write_mutex);
				set_int(&data->data_mutex, &data->is_died, 1);
			}
			pthread_mutex_unlock(&data->write_mutex);
		}
		if (get_int(&data->data_mutex, &data->is_died))
			break ;
		if (philo_full(data))
			break ;
	}
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	print_status(philo, "has taken a fork\n");
	ft_usleep(philo->data->time_to_die, philo->data);
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	if (data->nbr_philo == 1)
	{
		data->philos[0].last_meal = get_current_time();
		if (pthread_create(&data->philos[0].thread_id, NULL,
				one_philo, &(data->philos[0])))
			return (end_simulation(data), 1);
	}
	else
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			data->philos[i].last_meal = get_current_time();
			if (pthread_create(&data->philos[i].thread_id, NULL,
					routine, &(data->philos[i])))
				return (end_simulation(data), 1);
		}
	}
	main_thread_check(data);
	return (0);
}
