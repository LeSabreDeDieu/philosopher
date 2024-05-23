/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:01:33 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/23 20:02:16 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_philo *philo)
{
	pthread_mutex_init(&philo->r_fork, NULL);
	philo->last_meal = philo->start_time;
	philo->num_times_to_eat = -1;
}

void	init_philos(t_program *program)
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
		program->philos[i].dead_flag = &program->dead_flag;
		init_philo(&program->philos[i]);
		i++;
	}
	program->philos[0].l_fork = &program->philos[program->num_of_philos
		- 1].r_fork;
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, routine,
			&program->philos[i]);
		i++;
	}
}

void	init_t_program(t_program *program, char **argv)
{
	program->num_of_philos = ft_atoi(argv[1]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		program->philos[0].num_times_to_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	program->philos = ft_calloc(program->num_of_philos, sizeof(t_philo));
	init_philos(program);
}
