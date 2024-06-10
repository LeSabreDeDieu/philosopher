/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_get_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:42:17 by sgabsi            #+#    #+#             */
/*   Updated: 2024/06/10 12:52:15 by sgabsi           ###   ########.fr       */
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

int	get_nb_time_to_eat_secured(t_philo *philo)
{
	int	nb_time_eat;

	pthread_mutex_lock(philo->num_to_eat_lock);
	nb_time_eat = philo->num_to_eat;
	pthread_mutex_unlock(philo->num_to_eat_lock);
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
