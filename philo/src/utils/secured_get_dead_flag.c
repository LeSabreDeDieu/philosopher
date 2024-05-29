/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_get_dead_flag.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:42:17 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/24 15:31:42 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_dead_flag_secured(t_philo *philo)
{
	int	dead_flag;

	pthread_mutex_lock(philo->dead_lock);
	dead_flag = philo->dead_flag;
	pthread_mutex_unlock(philo->dead_lock);
	return (dead_flag);
}
