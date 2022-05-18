/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:02:51 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/09 19:23:30 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*On essaye de prendre les deux fourchettes, ça change si on est un philo pair
ou impaire pour ne pas tomber dans des deadlocks, donc on inverse la prise de
fourchette pour eviter ça. Pour prendre les fourchettes on utilise les 
mutex (comme demandé), comme ça les thread philo attendent que les, mutex
soient unlock pour pouvoir prendre les fourchette correspondantes*/

void	take_fork(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		/* printf(""); */
		pthread_mutex_lock(&philo->info->fork[philo->fork_r]);
		print_state(philo, FORKING);
		/* printf(""); */
		pthread_mutex_lock(&philo->info->fork[philo->fork_l]);
		print_state(philo, FORKING);
	}
	else
	{
		pthread_mutex_lock(&philo->info->fork[philo->fork_l]);
		print_state(philo, FORKING);
		pthread_mutex_lock(&philo->info->fork[philo->fork_r]);
		print_state(philo, FORKING);
	}
}

/*Ici on mange, on va noter la derniere fois qu'on a mangé, dormir
le temps qu'il faut (args), ajouter au philo, un de plus au
nombre de fois mangé (si c'est == au max, le philo n'a plus faim
Puis on unlock les mutex par rapport au sens de prises de fourchettes
des philo pair/impair (à l'envers)*/

void	eat(t_philo *philo)
{
	print_state(philo, EATING);
	pthread_mutex_lock(&philo->info->mutex);
	philo->last_eat = real_time(philo);
	philo->nb_eat += 1;
	if (philo->nb_eat == philo->info->nbmust_eat)
		philo->info->not_hungry += 1;
	pthread_mutex_unlock(&philo->info->mutex);
	ms_sleep(philo, philo->info->time2eat);
	
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_l]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_r]);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_r]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_l]);
	}
}

/*On va faire dormir le philo en fonction de time2sleep*/
void	philo_sleep(t_philo *philo)
{
	print_state(philo, SLEEPING);
	ms_sleep(philo, philo->info->time2sleep);
}

/*Le philo pense, on print son etat*/
void	think(t_philo *philo)
{
	print_state(philo, THINKING);
}
