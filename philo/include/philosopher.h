/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:34:06 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/31 12:11:48 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// colors
# define DEAD_COLOR "\033[0;31m"
# define SLEEP_COLOR "\033[0;32m"
# define FORK_COLOR "\033[0;35m"
# define EAT_COLOR "\033[0;36m"
# define THINK_COLOR "\033[0;33m"
# define RESET_COLOR "\033[0m"

typedef struct s_philo
{
	pthread_mutex_t	num_times_to_eat_lock;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*last_meal_lock;
	pthread_mutex_t	*dead_lock;
	pthread_t		thread;
	int				dead_flag;
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
	pthread_mutex_t	last_meal_lock;
	pthread_t		cheak_nb_eat;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_of_philos;
}					t_program;

//	utils functions
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_atoi(const char *str);
long				gettimeofday_ms(void);
void				destroy_free_all(t_program *program);

// check_user_input functions
int					check_user_input(t_program *program, char **argv);

// secured functions
void				secured_write(t_philo *philo, char *str, char *color);
int					get_dead_flag_secured(t_philo *philo);
int 				get_nb_time_to_eat_secured(t_philo *philo);
long				get_time_to_eat_secured(t_philo *philo);
long				get_last_meal_secured(t_philo *philo);


// init functions
int					init_t_program(t_program *program, char **argv);

// stats functions
int					is_eating(t_philo *philo);
int					is_sleeping(t_philo *philo);
int					is_thinking(t_philo *philo);
int					take_forks(t_philo *philo);
void				put_fork(t_philo *philo);

// check_death functions
int					check_death(t_program *program);
void				check_is_all_dead(t_program *program, int is_all_dead);

// launchers functions
void				launch_program(t_program *program);
void				*routine(void *arg);

#endif