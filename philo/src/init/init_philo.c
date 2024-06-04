/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:01:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/04 12:29:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

static void	lunch_routine(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
		pthread_create(&program->philos[i].thread, NULL, &routine,
			&program->philos[i]);
}

static void	init_philo(t_philo *philo)
{
	pthread_mutex_init(&philo->r_fork, NULL);
	pthread_mutex_init(&philo->num_times_to_eat_lock, NULL);
	philo->last_meal = philo->start_time;
	philo->dead_flag = 0;
}

static void	init_philos(t_program *program, int nb_time_eat)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].start_time = program->start_time;
		if (i != 0)
			program->philos[i].l_fork = &program->philos[i - 1].r_fork;
		program->philos[i].time_to_eat = program->time_to_eat;
		program->philos[i].time_to_sleep = program->time_to_sleep;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].last_meal_lock = &program->last_meal_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		init_philo(&program->philos[i]);
		program->philos[i].num_times_to_eat = nb_time_eat;
		i++;
	}
	program->philos[0].l_fork = &program->philos[program->num_of_philos
		- 1].r_fork;
}

static int	launch_philos(t_program *program)
{
	if (program->num_of_philos == 1)
	{
		printf("%s%ld %d %s%s\n", THINK_COLOR, (gettimeofday_ms()
				- program->start_time), 1, "is thinking", RESET_COLOR);
		printf("%s%ld %d %s%s\n", FORK_COLOR, (gettimeofday_ms()
				- program->start_time), 1, "has taken a fork", RESET_COLOR);
		usleep(program->time_to_die * 1000);
		printf("%s%ld %d %s%s\n", DEAD_COLOR, (gettimeofday_ms()
				- program->start_time), 1, "died", RESET_COLOR);
		return (1);
	}
	lunch_routine(program);
	return (0);
}

int	init_t_program(t_program *program, char **argv)
{
	int	nb_time_eat;

	nb_time_eat = -1;
	if (check_user_input(program, argv))
		return (1);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->last_meal_lock, NULL);
	program->philos = ft_calloc(program->num_of_philos, sizeof(t_philo));
	if (argv[5])
	{
		nb_time_eat = ft_atoi(argv[5]);
		if (nb_time_eat < 1 || ((long)program->num_of_philos) > INT_MAX)
		{
			printf("Error : \"le nombre de fois que chaque philo doit manger\" ");
			return (printf("est soit < 1 ou depasse le int max\n"), 1);
		}
	}
	pthread_create(&program->check_nb_eat, NULL, &check_nb_eat, program);
	program->start_time = gettimeofday_ms();
	init_philos(program, nb_time_eat);
	if (launch_philos(program))
		return (destroy_free_all(program), 1);
	return (0);
}
