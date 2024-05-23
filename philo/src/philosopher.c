/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:05:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/23 20:12:21 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	while (!(*((t_philo *)arg)->dead_flag))
	{
		if (!is_thinking(arg))
			break ;
		is_eating(arg);
		if (!is_sleeping(arg))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	program;
	int			i;

	ft_bzero(&program, sizeof(t_program));
	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	i = 0;
	program.start_time = gettimeofday_ms();
	init_t_program(&program, argv);
	while (1)
	{
		check_death(&program);
		pthread_mutex_lock(&program.dead_lock);
		if (program.dead_flag)
		{
			break ;
		}
		pthread_mutex_unlock(&program.dead_lock);
	}
	while (i < program.num_of_philos)
	{
		pthread_join(program.philos[i].thread, NULL);
		i++;
	}
	free(program.philos);
	return (0);
}
