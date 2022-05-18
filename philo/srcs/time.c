/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:51:01 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/01 13:03:03 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*On utilise la fonction gettimeofday pour savoir quel temps il est
et on convertie les microsecondes en milisecondes car tout le sujet est en ms
1 ms = 1000us donc * 1000 */

size_t	what_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/*On calcule le temps depuis qu on a lancé le programme*/
size_t	real_time(t_philo *philo)
{
	return (what_time_ms() - philo->info->start);
}

/*Un sleep en ms, car le usleep ne marche pas bien, il créait des decalages*/
void	ms_sleep(t_philo *philo, size_t ms_sec_time)
{
	size_t	start;

	start = what_time_ms();
	while ((what_time_ms() - start < ms_sec_time) && philo->info->stop != 1)
		usleep(10);
}
