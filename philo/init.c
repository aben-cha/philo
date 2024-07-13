/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:25:34 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/25 09:26:23 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->data_mutex, NULL))
		return (pthread_mutex_destroy(&data->write_mutex), 1);
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (pthread_mutex_destroy(&data->write_mutex),
				pthread_mutex_destroy(&data->data_mutex), 1);
	}
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nbr_meals_eat = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].right_fork = i;
		data->philos[i].left_fork = (i + 1) % data->nbr_philo;
		data->philos[i].data = data;
	}
}

int	ft_init(t_data *data)
{
	if (mutex_init(data))
		return (write(2, "Error init mutex.\n", 18), 1);
	philo_init(data);
	return (0);
}
