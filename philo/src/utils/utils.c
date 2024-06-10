/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:30:38 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/10 12:58:37 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

static int	check_user_input_2(t_program *program, char **argv)
{
	program->time_to_sleep = ft_atoi(argv[4]);
	if (program->time_to_sleep < 1 || ((long)program->num_of_philos) > INT_MAX)
	{
		printf("Error : le \"time to sleep\" ");
		return (printf("est soit < 1 ou depasse le int max\n"), 1);
	}
	return (0);
}

int	check_user_input(t_program *program, char **argv)
{
	program->num_of_philos = ft_atoi(argv[1]);
	if (program->num_of_philos < 1 || ((long)program->num_of_philos) > INT_MAX)
	{
		printf("Error : le nombre de philo ");
		return (printf("est soit < 1 ou depasse le int max\n"), 1);
	}
	program->time_to_eat = ft_atoi(argv[3]);
	if (program->time_to_eat < 1 || ((long)program->num_of_philos) > INT_MAX)
	{
		printf("Error : ");
		return (printf("le \"time to eat\" est soit < 1 ou depasse le int max\n"),
			1);
	}
	program->time_to_die = ft_atoi(argv[2]);
	if (program->time_to_die < 1 || ((long)program->num_of_philos) > INT_MAX)
	{
		printf("Error : ");
		return (printf("le \"time to die\" est soit < 1 ou depasse le int max\n"),
			1);
	}
	if (check_user_input_2(program, argv) == 1)
		return (1);
	return (0);
}

void	init_mutex(t_program *program)
{
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->last_meal_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->num_to_eat_lock, NULL);
}
