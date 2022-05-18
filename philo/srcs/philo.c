/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:46:05 by ndormoy           #+#    #+#             */
/*   Updated: 2022/02/09 19:19:27 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info			*info;

	if (ft_check_args(argc, argv) == 0)
	{
		ft_error();
		return (FALSE);
	}
	info = ft_init(argc, argv);
	if (!info)
		return (FALSE);
	ft_create_philo(info);
	ft_clean(info->philo);
}
