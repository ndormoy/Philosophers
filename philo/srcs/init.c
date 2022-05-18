/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:46:27 by ndormoy           #+#    #+#             */
/*   Updated: 2022/01/31 13:51:40 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	atoi;
	int				neg;

	neg = 1;
	atoi = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		atoi = atoi * 10 + *str - 48;
		str++;
	}
	return (atoi * neg);
}

static t_info	*ft_init_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->fork)
		return (NULL);
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&info->fork[i], NULL);
		pthread_mutex_init(&info->philo[i].mutex_philo, NULL);
		pthread_mutex_init(&info->philo[i].mutex_print, NULL);
		i++;
	}
	pthread_mutex_init(&info->mutex, NULL);
	return (info);
}

/*On initialise a 0 le tableau de philo (contenu dans la struct info)*/

static t_info	*ft_init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info)
		return (NULL);
	while (i < info->nb_philo)
	{
		memset(&info->philo[i], 0, sizeof(t_philo));
		info->philo[i].index = i;
		info->philo[i].info = info;
		info->philo[i].last_eat = 0;
		info->philo[i].nb_eat = 0;
		info->philo[i].fork_l = 0;
		info->philo[i].fork_r = 0;
		i++;
	}
	return (info);
}

/*On intialise les infos generales des philo dans la struct
info, ces infos viennent des argument du main (argv)...*/

static t_info	*ft_init_info(int argc, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	memset(info, 0, sizeof(t_info));
	info->nb_philo = ft_atoi(argv[1]);
	info->time2die = ft_atoi(argv[2]);
	info->time2eat = ft_atoi(argv[3]);
	info->time2sleep = ft_atoi(argv[4]);
	info->start = 0;
	info->stop = 0;
	info->not_hungry = 0;
	if (argc == 6)
		info->nbmust_eat = ft_atoi(argv[5]);
	else
		info->nbmust_eat = -1;
	return (info);
}

/*Cette fonction permet d'inialiser les info et le tableau de philo*/

t_info	*ft_init(int argc, char **argv)
{
	t_info	*info;

	info = ft_init_info(argc, argv);
	if (!info)
		return (NULL);
	info = ft_init_philo(info);
	if (!info->philo)
	{
		free(info);
		return (NULL);
	}
	info = ft_init_mutex(info);
	if (!info->fork)
	{
		free(info->philo);
		free(info);
		return (NULL);
	}
	return (info);
}
