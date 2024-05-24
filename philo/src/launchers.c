/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:09:03 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/24 16:49:58 by sgabsi           ###   ########.fr       */
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
	while (!is_all_dead)
	{
		i = -1;
		while (++i < program->num_of_philos)
		{
			pthread_mutex_lock(&program->philos[i].num_times_to_eat_lock);
			if (program->philos[i].num_times_to_eat != 0)
				is_all_dead = 0;
			pthread_mutex_unlock(&program->philos[i].num_times_to_eat_lock);
		}
		usleep(500);
	}
	i = -1;
	while (++i < program->num_of_philos)
		pthread_join(program->philos[i].thread, NULL);
	free(program->philos);
}
