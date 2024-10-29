/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trylock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:10:46 by sgabsi            #+#    #+#             */
/*   Updated: 2024/10/28 12:21:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	int	result;

	result = pthread_mutex_lock(mutex);
	if (result != 0)
		printf("Error : Unexpected error when try to lock mutex");
	return (result);
}
