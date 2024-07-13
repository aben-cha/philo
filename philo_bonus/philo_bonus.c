/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:18:10 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:19:36 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	t_data	data;

	if (!(ac == 5 || ac == 6))
		return (write(2, "the number of args should 5 or 6.\n", 34), 1);
	if (parsing(ac, av, &data))
		return (1);
	if (ft_init(&data))
		return (1);
	if (start_simulation(&data))
		return (1);
	clean_data(&data);
	return (0);
}
