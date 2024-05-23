/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:55 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/23 20:13:15 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	is_eating(t_philo *philo)
{
	secured_write(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	philo->last_meal = gettimeofday_ms();
	if (philo->num_times_to_eat > 0)
		philo->num_times_to_eat--;
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	is_sleeping(t_philo *philo)
{
	if (*philo->dead_flag)
		return (0);
	secured_write(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	return (1);
}

int	is_thinking(t_philo *philo)
{
	if (*philo->dead_flag)
		return (0);
	secured_write(philo, "is thinking");
	pthread_mutex_lock(philo->l_fork);
	secured_write(philo, "has taken a fork");
	pthread_mutex_lock(&philo->r_fork);
	secured_write(philo, "has taken a fork");
	return (1);
}
