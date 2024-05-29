/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:57:15 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/28 14:08:07 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_is_all_dead(t_program *program, int is_all_dead)
{
	int	i;

	while (!is_all_dead)
	{
		i = -1;
		while (++i < program->num_of_philos)
		{
			pthread_mutex_lock(&program->philos[i].num_times_to_eat_lock);
			if (program->philos[i].num_times_to_eat != 0)
				is_all_dead = 0;
			else
				is_all_dead = 1;
			pthread_mutex_unlock(&program->philos[i].num_times_to_eat_lock);
		}
	}
}
