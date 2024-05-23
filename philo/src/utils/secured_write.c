/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:44:08 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/23 19:52:54 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	secured_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%ld %d %s\n", (gettimeofday_ms() - philo->start_time), philo->id,
		str);
	pthread_mutex_unlock(philo->write_lock);
}
