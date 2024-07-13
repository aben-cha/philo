/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:20:48 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 00:38:11 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			res;

	if (gettimeofday(&tv, NULL) == -1)
		return (write(2, "An error occurred while getting the time.\n", 42), 1);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	ft_usleep(long ms, t_data *data)
{
	long	start;

	start = get_current_time();
	while (((get_current_time() - start) < ms))
	{
		if (get_int(&data->data_mutex, &data->is_died))
			break ;
		usleep(500);
	}
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (1);
	}
	return (0);
}

int	end_simulation(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_destroy(&data->write_mutex))
		return (1);
	if (pthread_mutex_destroy(&data->data_mutex))
		return (1);
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			return (1);
	}
	return (0);
}
