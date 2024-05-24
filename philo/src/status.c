/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:55 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/24 16:46:01 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdio.h>
#include <unistd.h>

int	is_eating(t_philo *philo)
{
	if (get_dead_flag_secured(philo) || philo->num_times_to_eat == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		return (0);
	}
	pthread_mutex_lock(philo->last_meal_lock);
	philo->last_meal = gettimeofday_ms();
	pthread_mutex_unlock(philo->last_meal_lock);
	secured_write(philo, "is eating", EAT_COLOR);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->num_times_to_eat_lock);
	if (philo->num_times_to_eat > 0)
		philo->num_times_to_eat--;
	pthread_mutex_unlock(&philo->num_times_to_eat_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	return (1);
}

int	is_sleeping(t_philo *philo)
{
	if (get_dead_flag_secured(philo) || philo->num_times_to_eat == 0)
		return (0);
	secured_write(philo, "is sleeping", SLEEP_COLOR);
	usleep(philo->time_to_sleep * 1000);
	return (1);
}

int	is_thinking(t_philo *philo)
{
	if (get_dead_flag_secured(philo) || philo->num_times_to_eat == 0)
		return (0);
	if (philo->id % 2 == 0)
		usleep(5000);
	secured_write(philo, "is thinking", THINK_COLOR);
	if (!get_dead_flag_secured(philo) && philo->num_times_to_eat != 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		secured_write(philo, "has taken a fork", FORK_COLOR);
	}
	else
		return (0);
	if (!get_dead_flag_secured(philo) && philo->num_times_to_eat != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		secured_write(philo, "has taken a fork", FORK_COLOR);
	}
	else
		return (pthread_mutex_unlock(&philo->r_fork), 0);
	return (1);
}
