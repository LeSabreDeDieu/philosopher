/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:38:01 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/07 11:01:34 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	set_all_philos_died(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		if (get_dead_flag_secured(&program->philos[i]) != 1)
		{
			pthread_mutex_lock(program->philos[i].dead_lock);
			program->philos[i].dead_flag = 1;
			pthread_mutex_unlock(program->philos[i].dead_lock);
		}
	}
	return (1);
}

void	*check_nb_eat(void *arg)
{
	int			i;
	t_program	*program;

	i = -1;
	program = (t_program *)arg;
	while (get_nb_time_to_eat_secured(&program->philos[0]) >= 0)
	{
		while (++i < program->num_of_philos)
		{
			if (get_nb_time_to_eat_secured(&program->philos[i]) == 0)
			{
				pthread_mutex_lock(&program->dead_lock);
				program->philos[i].dead_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
			}
		}
	}
	return (NULL);
}

int	check_death(t_program *program)
{
	int		i;
	int		num_eat;
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
			pthread_mutex_lock(&program->write_lock);
			num_eat = get_nb_time_to_eat_secured(&program->philos[i]);
			if (num_eat < 0 || num_eat > 0)
				printf("%s%ld %d %s%s\n", DEAD_COLOR, (gtod
						- program->start_time), program->philos[i].id, "died",
					RESET_COLOR);
			pthread_mutex_unlock(&program->write_lock);
			pthread_mutex_unlock(&program->dead_lock);
			return (set_all_philos_died(program));
		}
	}
	return (0);
}
