/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:38:01 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/31 12:16:33 by sgabsi           ###   ########.fr       */
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

void	*check_nb_eat(void *arg)
(
	while (get_nb_time_to_eat_secured((t_philo)&arg->philos[0]) != -1)
	{
			
	}
)

int	check_death(t_program *program)
{
	int		i;
	long	gtod;

	i = -1;
	gtod = 0;
	while (++i < program->num_of_philos)
	{
		gtod = gettimeofday_ms();
		if (gtod - get_last_meal_secured(&program->philos[i])
			>= program->time_to_die)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->philos[i].dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			pthread_mutex_lock(&program->write_lock);
			printf("%s%ld %d %s%s\n", DEAD_COLOR, (gtod	- program->start_time),
				program->philos[i].id, "died", RESET_COLOR);
			pthread_mutex_unlock(&program->write_lock);
			set_all_philos_died(program);
			return (1);
		}
	}
	return (0);
}
