/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:13:32 by sgabsi            #+#    #+#             */
/*   Updated: 2024/05/29 06:39:11 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	take_forks_left(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	secured_write(philo, "has taken a fork", FORK_COLOR);
}

static void	take_forks_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	secured_write(philo, "has taken a fork", FORK_COLOR);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!get_dead_flag_secured(philo) && philo->num_times_to_eat != 0)
			take_forks_left(philo);
		else
			return (0);
		if (!get_dead_flag_secured(philo) && philo->num_times_to_eat != 0)
			take_forks_right(philo);
		else
			return (pthread_mutex_unlock(philo->l_fork), 0);
	}
	else
	{
		if (!get_dead_flag_secured(philo) && philo->num_times_to_eat != 0)
			take_forks_right(philo);
		else
			return (0);
		if (!get_dead_flag_secured(philo) && philo->num_times_to_eat != 0)
			take_forks_left(philo);
		else
			return (pthread_mutex_unlock(&philo->r_fork), 0);
	}
	return (1);
}

void	put_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
}
