/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:44:08 by sgabsi            #+#    #+#             */
/*   Updated: 2024/07/02 16:35:05 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	secured_write(t_philo *philo, char *str, char *color)
{
	if (get_dead_flag_secured(philo))
		return ;
	pthread_mutex_lock(philo->write_lock);
	printf("%s%ld %d %s%s\n", color, (gettimeofday_ms() - philo->start_time),
		philo->id, str, R);
	pthread_mutex_unlock(philo->write_lock);
}
