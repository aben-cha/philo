/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:41:23 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/25 09:07:28 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	check_string(char *av)
{
	int	i;

	i = 0;
	while (av[i] == ' ' || (av[i] >= 9 && av[i] <= 13))
		i++;
	if (av[i] == '-')
		return (1);
	if (av[i] == '+')
		i++;
	if (av[i] == ' ' || av[i] == '\0')
		return (1);
	while (av && av[i] && av[i] != ' ')
	{
		if (!ft_isdigit(av[i]))
			return (1);
		i++;
	}
	while (av[i] == ' ' || (av[i] >= 9 && av[i] <= 13))
		i++;
	if (av[i] != ' ' && av[i] != '\0')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && result <= INT_MAX)
		result = (result * 10) + str[i++] - '0';
	return (result);
}

int	parsing(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (check_string(av[i]) || ft_atoi(av[i]) > INT_MAX)
			return (write(2, "Error in parsing\n", 17), 1);
	}
	data->full_data = 0;
	data->is_died = 0;
	data->nbr_philo = ft_atoi(av[1]);
	if (data->nbr_philo > 200)
		return (write(2, "Nbr_philos should lower than 200.\n", 34), 1);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nbr_limit_meals = ft_atoi(av[5]);
	else
		data->nbr_limit_meals = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->nbr_philo <= 0
		|| (av[5] && data->nbr_limit_meals <= 0))
		return (write(2, "wrong argument.\n", 16), 1);
	return (0);
}
