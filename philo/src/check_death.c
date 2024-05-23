/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:38:01 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/23 19:43:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_death(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (gettimeofday_ms()
			- program->philos[i].last_meal > program->time_to_die)
		{
			pthread_mutex_lock(program->philos[i].write_lock);
			printf("%ld %d died\n", (gettimeofday_ms() - program->start_time),
				program->philos[i].id);
			pthread_mutex_unlock(program->philos[i].write_lock);
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return ;
		}
		i++;
	}
}
