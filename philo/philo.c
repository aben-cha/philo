/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:44:06 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/25 08:36:21 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (join_threads(&data))
		return (1);
	if (end_simulation(&data))
		return (1);
	return (0);
}
