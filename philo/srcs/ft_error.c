/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:25:49 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/01 10:48:20 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
}

void	ft_clean(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->info->mutex);
	pthread_mutex_destroy(&philo->mutex_print);
	pthread_mutex_destroy(&philo->mutex_philo);
	while (i < philo->info->nb_philo)
	{
		pthread_mutex_destroy(&philo->info->fork[i]);
		i++;
	}
	free(philo->info->fork);
	free(philo->info);
	free(philo);
}
