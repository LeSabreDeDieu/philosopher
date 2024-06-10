/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:09:03 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/10 12:09:49 by sgabsi           ###   ########.fr       */
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
	}
	free(program->philos);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->last_meal_lock);
	pthread_mutex_destroy(&program->num_to_eat_lock);
}

void	launch_program(t_program *program)
{
	int	i;

	while (1)
		if (check_death(program))
			break ;
	i = -1;
	while (++i < program->num_of_philos)
		pthread_join(program->philos[i].thread, NULL);
	destroy_free_all(program);
}
