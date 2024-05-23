/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:34:06 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/23 20:12:42 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_t		thread;
	int				*dead_flag;
	long			start_time;
	long			time_to_eat;
	long			time_to_sleep;
	long			last_meal;
	int				id;
	int				num_times_to_eat;
}					t_philo;

typedef struct s_program
{
	t_philo			*philos;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				dead_flag;
	int				num_of_philos;
}					t_program;

// recreation of libc functions
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
long	gettimeofday_ms(void);
void	secured_write(t_philo *philo, char *str);

// init functions
void	init_t_program(t_program *program, char **argv);

// routine functions
void	*routine(void *arg);

// stats functions
void	is_eating(t_philo *philo);
int		is_sleeping(t_philo *philo);
int		is_thinking(t_philo *philo);

// check_death functions
void	check_death(t_program *program);

#endif