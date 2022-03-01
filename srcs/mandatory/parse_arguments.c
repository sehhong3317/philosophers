/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:35:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/02/22 12:00:34 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atoi(char *str)
{
	long long	nbr;
	int			num_of_digits;

	nbr = 0;
	num_of_digits = 0;
	if (*str == '-' || *str == '+')
		return (-1);
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num_of_digits++;
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (*str || num_of_digits > 10 || nbr > 2147483647)
		return (-1);
	return ((long)nbr);
}

static void	initiate_info(t_info *info)
{
	// info->vital = 0;
	info->dead_philo = -1;
	info->death_msg = 0;
	info->meal_done = 0;
	info->num_of_meal = -1;
}

int	parse_arguments(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (-1);
	initiate_info(info);
	info->num_of_philo = (int)ft_atoi(argv[1]);
	info->time_to_die = (time_t)ft_atoi(argv[2]);
	info->time_to_eat = (time_t)ft_atoi(argv[3]);
	info->time_to_sleep = (time_t)ft_atoi(argv[4]);
	if (argc == 6)
	{	
		info->num_of_meal = (int)ft_atoi(argv[5]);
		if (info->num_of_meal < 1)
			return (-1);
	}
	if (info->num_of_philo < 1 || info->time_to_die <= 0 \
		|| info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (-1);
	return (0);
}
