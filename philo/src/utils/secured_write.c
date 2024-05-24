/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:44:08 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/24 16:42:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	secured_write(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(philo->write_lock);
	if (get_dead_flag_secured(philo))
	{
		printf("%s%ld %d %s%s\n", DEAD_COLOR, (gettimeofday_ms()
				- philo->start_time), philo->id, "died", RESET_COLOR);
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	printf("%s%ld %d %s%s\n", color, (gettimeofday_ms() - philo->start_time),
		philo->id, str, RESET_COLOR);
	pthread_mutex_unlock(philo->write_lock);
}
