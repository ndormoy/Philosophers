/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:10:18 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/09 19:29:53 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*On print l'etat du philo, on fonction de ce qui est envoyé,
on calcule et on affiche le temps ou l'action a ete realisée*/

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->stop == 1
		|| philo->info->not_hungry == (int)philo->info->nb_philo)
	{
		pthread_mutex_unlock(&philo->info->mutex);
		return ;	
	}
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_lock(&philo->mutex_print);
	printf("%ld [%d] %s\n", real_time(philo), philo->index + 1, state);
	pthread_mutex_unlock(&philo->mutex_print);
}
