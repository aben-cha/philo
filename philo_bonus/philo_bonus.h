/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:18:05 by aben-cha          #+#    #+#             */
/*   Updated: 2024/06/14 15:37:32 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define SEM_DATA  "/sem_data"
# define SEM_FORKS "/sem_forks"
# define SEM_WRITE "/sem_write"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	int			philo_pid;
	int			nbr_meals_eat;
	int			left_fork;
	int			right_fork;
	long		last_meal;
	pthread_t	monitor_thread;
	t_data		*data;
}			t_philo;

struct	s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_limit_meals;
	int				is_died;
	int				counter;
	long			start_time;
	t_philo			philos[200];
	sem_t			*write_sem;
	sem_t			*data_sem;
	sem_t			*forks;
};

int		ft_isdigit(int c);
int		check_string(char *av);
long	ft_atoi(const char *str);
int		parsing(int ac, char **av, t_data *data);
int		semaphore_init(t_data *data);
void	philo_init(t_data *data);
int		ft_init(t_data *data);
int		philo_died(t_philo *philo);
int		one_philo(t_philo *philo);
int		philo_full(t_philo *philo);
void	*main_check(void *philo_data);
int		start_simulation(t_data *data);
void	routine(t_philo *philo);
void	print_status(t_philo *philo, char *string);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
long	get_current_time(void);
void	ft_usleep(long ms, t_data *data);
void	kill_processes(t_data *data);
void	clean_data(t_data *data);
void	set_int(sem_t *sem, int *value, int new_value);
int		get_int(sem_t *sem, int *value);
long	get_long(sem_t *sem, long *value);

#endif