/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:18:23 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:18:28 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	semaphore_init(t_data *data)
{
	sem_unlink(SEM_DATA);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	data->data_sem = sem_open(SEM_DATA, O_CREAT | O_EXCL, 0644, 1);
	data->write_sem = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, data->nbr_philo);
	if (data->write_sem == SEM_FAILED || data->data_sem == SEM_FAILED
		|| data->forks == SEM_FAILED)
		return (write(2, "Error open semaphore.\n", 23), 1);
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].philo_pid = 0;
		data->philos[i].nbr_meals_eat = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
	}
}

int	ft_init(t_data *data)
{
	if (semaphore_init(data))
		return (1);
	philo_init(data);
	return (0);
}
