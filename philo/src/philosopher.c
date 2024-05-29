/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:05:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/28 22:18:59 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	usage(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	main(int argc, char **argv)
{
	t_program	program;
	int			i;

	if (!(argc == 5 || argc == 6))
		return (usage(), 1);
	ft_bzero(&program, sizeof(t_program));
	i = 0;
	if (init_t_program(&program, argv))
		return (1);
	launch_program(&program);
	return (0);
}
