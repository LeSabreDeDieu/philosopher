/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:09:03 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/28 23:02:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	int	dead_flag;

	dead_flag = get_dead_flag_secured(arg);
	while (!dead_flag)
	{
		if (!is_thinking(arg))
			break ;
		if (!is_eating(arg))
			break ;
		if (!is_sleeping(arg))
			break ;
		dead_flag = get_dead_flag_secured(arg);
	}
	return (NULL);
}

void	destroy_free_all(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		pthread_mutex_destroy(&program->philos[i].r_fork);
		pthread_mutex_destroy(&program->philos[i].num_times_to_eat_lock);
	}
	free(program->philos);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->last_meal_lock);
}

void	launch_program(t_program *program)
{
	int	i;
	int	is_all_dead;

	is_all_dead = 0;
	while (program->philos[0].num_times_to_eat == -1)
		if (check_death(program))
			break ;
	if (program->philos[0].num_times_to_eat == -1)
		is_all_dead = 1;
	check_is_all_dead(program, is_all_dead);
	i = -1;
	while (++i < program->num_of_philos)
		pthread_join(program->philos[i].thread, NULL);
	destroy_free_all(program);
}
