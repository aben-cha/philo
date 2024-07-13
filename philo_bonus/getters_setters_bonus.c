/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:18:34 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:18:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_int(sem_t *sem, int *value, int new_value)
{
	sem_wait(sem);
	*value = new_value;
	sem_post(sem);
}

int	get_int(sem_t *sem, int *value)
{
	int	ret;

	sem_wait(sem);
	ret = *value;
	sem_post(sem);
	return (ret);
}

long	get_long(sem_t *sem, long *value)
{
	long	ret;

	sem_wait(sem);
	ret = *value;
	sem_post(sem);
	return (ret);
}
