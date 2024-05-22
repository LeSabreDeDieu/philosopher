/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:05:24 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/22 17:42:29 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (init_program(&program, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (start_simulation(&program))
	{
		printf("Error: Simulation failed\n");
		return (1);
	}
	return (0);
}