/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:38:01 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/28 14:29:45 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	set_all_philos_died(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		pthread_mutex_lock(program->philos[i].dead_lock);
		program->philos[i].dead_flag = 1;
		pthread_mutex_unlock(program->philos[i].dead_lock);
	}
}

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
			pthread_mutex_lock(&program->write_lock);
			printf("%s%ld %d %s%s\n", DEAD_COLOR, (gettimeofday_ms()
					- program->start_time), program->philos[i].id, "died",
				RESET_COLOR);
			pthread_mutex_unlock(&program->write_lock);
			pthread_mutex_unlock(&program->dead_lock);
			pthread_mutex_unlock(program->philos[i].last_meal_lock);
			set_all_philos_died(program);
			return (1);
		}
		pthread_mutex_unlock(program->philos[i].last_meal_lock);
	}
	return (0);
}
