/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday_ms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:18:43 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/02 17:02:28 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <sys/time.h>

long	gettimeofday_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

int	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = gettimeofday_ms();
	while (gettimeofday_ms() - start < time)
	{
		if (get_dead_flag_secured(philo))
			return (1);
		usleep(100);
	}
	return (0);
}
