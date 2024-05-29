/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_get_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:42:17 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/29 03:46:37 by sgabsi           ###   ########.fr       */
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

int get_time_to_eat_secured(t_philo *philo)
{
	int	time_to_eat;

	pthread_mutex_lock(philo->write_lock);
	time_to_eat = philo->time_to_eat;
	pthread_mutex_unlock(philo->write_lock);
	return (time_to_eat);
}
