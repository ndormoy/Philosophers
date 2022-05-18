/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:46:29 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/09 19:32:40 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*On regarde si le philo passé en arguement est entrain de mourir de faim, si
oui on revoie 1, et on affiche le philo mort. Usleep pour eviter les problemes
d'affichage*/

static int	philo_starving(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (real_time(philo) - philo->last_eat > philo->info->time2die)
	{
		philo->info->stop = 1;
		usleep(1000);
		printf("%ldms [%d] %s\n", real_time(philo),
			philo->index + 1, DYING);
		pthread_mutex_unlock(&philo->info->mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->info->mutex);
	return (FALSE);
}

/*Cette fonction est enfait un Thread, pendant toute la durée du programme
on va checker si un philo est mort à l'aide de la fonction ci-dessus.
Si oui la variable philo->info->stop est mise a 1, ce qui va arrêter le 
programme par réaction en chaîne*/

static void	*ft_check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->info->stop != 1)	
	{
		i = 0;
		while (i < philo->info->nb_philo && philo->info->stop != 1)
		{
			pthread_mutex_lock(&philo->info->mutex);
			if (philo->info->not_hungry == philo->info->nb_philo)
			{
				pthread_mutex_unlock(&philo->info->mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->info->mutex);
			if (philo_starving(&philo[i]))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&philo->info->mutex);
		if (philo->info->not_hungry == philo->info->nb_philo)
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->mutex);
		usleep(500);
	}
	return (NULL);
}

/*Cette fonction est celle utilisée par tous les thread philo.
Elle va tourner en boucle jusqu'à ce que l'un des philo meurt où que
les philo ont terminé de manger*/

static void	*ft_actions_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->fork_l = philo->index;
	philo->fork_r = (philo->index + 1) % philo->info->nb_philo;
	if (philo->info->nb_philo == 1)
	{
		print_state(philo, FORKING);
		return (NULL);
	}
	while (philo->info->stop == 0)
	{
		take_fork(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
		pthread_mutex_lock(&philo->info->mutex);
		if (philo->info->not_hungry == (int)philo->info->nb_philo)
		{
			pthread_mutex_unlock(&philo->info->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->mutex);
	}
	return (NULL);
}

/*Permet de lancer les threads, on lance le nb de thread équivalent au nb
de philo. Apres on lance le "thread" Check_Death (Pas besoin de pthread_create
car c'est le thread du main), et on join les threads philo pour eviter que 
le thread main ne s'execute trop rapidement et ne laisse pas les thread philo
tourner*/

void	ft_create_philo(t_info *info)
{
	int	i;

	i = 0;
	info->start = what_time_ms();
	while (i < info->nb_philo)
	{
		pthread_create(&info->philo[i].thread, NULL, &ft_actions_philo,
			(void*)&(info->philo[i]));
		i ++;
	}
	ft_check_death(info->philo);
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
}
