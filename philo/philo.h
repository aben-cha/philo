/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:43:43 by aben-cha          #+#    #+#             */
/*   Updated: 2024/07/13 08:44:37 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	int			nbr_meals_eat;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	pthread_t	thread_id;
	t_data		*data;
}			t_philo;

struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_limit_meals;
	int				is_died;
	int				full_data;
	long			start_time;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
};
long	ft_atoi(const char *str);
int		check_string(char *av);
int		ft_isdigit(int c);
int		parsing(int ac, char **av, t_data *data);
int		mutex_init(t_data *data);
void	philo_init(t_data *data);
int		ft_init(t_data *data);
int		philo_died(t_philo *philo);
int		philo_full(t_data *data);
void	main_thread_check(t_data *data);
void	*one_philo(void *data);
int		start_simulation(t_data *data);
void	*routine(void *philo_data);
void	print_status(t_philo *philo, char *string);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
long	get_current_time(void);
void	ft_usleep(long ms, t_data *data);
int		join_threads(t_data *data);
int		end_simulation(t_data *data);
void	set_int(pthread_mutex_t *mutex, int *value, int new_value);
int		get_int(pthread_mutex_t *mutex, int *value);
long	get_long(pthread_mutex_t *mutex, long *value);

#endif