/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_get_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:42:17 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/29 05:32:16 by sgabsi           ###   ########.fr       */
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

long get_time_to_eat_secured(t_philo *philo)
{
	long	time_to_eat;

	pthread_mutex_lock(philo->write_lock);
	time_to_eat = philo->time_to_eat;
	pthread_mutex_unlock(philo->write_lock);
	return (time_to_eat);
}

int get_nb_time_to_eat_secured(t_philo *philo)
{
	int	nb_time_eat;

	pthread_mutex_lock(&philo->num_times_to_eat_lock);
	nb_time_eat = philo->num_times_to_eat;
	pthread_mutex_unlock(&philo->num_times_to_eat_lock);
	return (nb_time_eat);
}

long	get_last_meal_secured(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(philo->last_meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(philo->last_meal_lock);
	return (last_meal);
}