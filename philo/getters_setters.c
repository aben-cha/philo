/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:58:32 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 17:43:24 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t *mutex, int *value, int new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}
