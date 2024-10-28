/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:19:55 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/28 10:33:44 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdio.h>
#include <unistd.h>

int	is_eating(t_philo *philo)
{
	if (get_dead_flag_secured(philo) || philo->num_to_eat == 0)
		return (put_fork(philo), 0);
	pthread_mutex_lock(philo->last_meal_lock);
	philo->last_meal = gettimeofday_ms();
	pthread_mutex_unlock(philo->last_meal_lock);
	secured_write(philo, "is eating", EAT_COLOR);
	if (ft_usleep(philo->time_to_eat, philo))
		return (put_fork(philo), 0);
	if (get_nb_time_to_eat_secured(philo) > 0)
	{
		pthread_mutex_lock(philo->num_to_eat_lock);
		philo->num_to_eat--;
		if (philo->num_to_eat == 0)
		{
			pthread_mutex_lock(philo->finish_eating_lock);
			philo->is_finish_eating = true;
			pthread_mutex_unlock(philo->finish_eating_lock);
			return (pthread_mutex_unlock(philo->num_to_eat_lock),
				put_fork(philo), 0);
		}
		pthread_mutex_unlock(philo->num_to_eat_lock);
	}
	return (put_fork(philo), 1);
}

int	is_sleeping(t_philo *philo)
{
	if (get_dead_flag_secured(philo) || philo->num_to_eat == 0)
		return (0);
	secured_write(philo, "is sleeping", SLEEP_COLOR);
	if (ft_usleep(philo->time_to_sleep, philo))
		return (0);
	return (1);
}

int	is_thinking(t_philo *philo)
{
	int	think_time;

	think_time = 0;
	if (get_dead_flag_secured(philo) || philo->num_to_eat == 0)
		return (0);
	secured_write(philo, "is thinking", THINK_COLOR);
	if (philo->num_of_philos % 2 != 0)
	{
		if (philo->num_of_philos % 2 != 0
			&& philo->time_to_eat > philo->time_to_sleep)
			think_time = philo->time_to_eat - philo->time_to_sleep;
		if (philo->id % 2 != 0)
		{
			if (ft_usleep(((philo->time_to_eat / 2) + think_time), philo))
				return (0);
		}
		else
			ft_usleep(think_time, philo);
	}
	if (!take_forks(philo))
		return (0);
	return (1);
}
