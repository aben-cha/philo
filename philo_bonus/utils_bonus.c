/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:17:43 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:32:12 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		if (get_int(data->data_sem, &data->is_died))
			break ;
		usleep(500);
	}
}

void	kill_processes(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->nbr_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->nbr_philo)
				kill(data->philos[i].philo_pid, SIGTERM);
			break ;
		}
	}
}

void	clean_data(t_data *data)
{
	kill_processes(data);
	sem_close(data->data_sem);
	sem_close(data->write_sem);
	sem_close(data->forks);
	sem_unlink(SEM_DATA);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
}
