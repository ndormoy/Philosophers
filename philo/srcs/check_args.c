/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:46:32 by ndormoy           #+#    #+#             */
/*   Updated: 2022/01/31 14:07:20 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	unsigned long long	atoll;
	int					neg;

	neg = 1;
	atoll = 0;
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
		atoll = atoll * 10 + *str - 48;
		str++;
	}
	return ((long long)atoll * neg);
}

int	ft_over_limits(size_t nb)
{
	if (nb > 2147483647)
		return (1);
	return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc <= 4 || argc >= 7)
		return (0);
	while (argv[i])
	{
		j = 0;
		if (ft_over_limits(ft_atoll(argv[i])))
			return (0);
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
