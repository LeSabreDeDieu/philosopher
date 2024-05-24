/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:38:01 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/24 16:49:42 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		pthread_mutex_lock(program->philos[i].last_meal_lock);
		if (gettimeofday_ms()
			- program->philos[i].last_meal > program->time_to_die)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->philos[i].dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			pthread_mutex_unlock(program->philos[i].last_meal_lock);
			i = -1;
			while (++i < program->num_of_philos)
			{
				pthread_mutex_lock(program->philos[i].dead_lock);
				program->philos[i].dead_flag = 1;
				pthread_mutex_unlock(program->philos[i].dead_lock);
			}
			return (1);
		}
		pthread_mutex_unlock(program->philos[i].last_meal_lock);
	}
	return (0);
}
