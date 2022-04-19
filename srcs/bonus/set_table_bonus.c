/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:03:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/18 11:21:45 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	initiate_box(t_box *box)
{
	box->num_of_philo = 0;
	box->time_to_die = 0;
	box->time_to_eat = -1;
	box->time_to_sleep = -1;
	box->min_meal = 0;
}

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

static	void	parse_args(int argc, char **argv, t_box *box)
{
	if (argc != 5 && argc != 6)
		exit_with_err("Invalid number of arguments");
	box->num_of_philo = (int)ft_atoi(argv[1]);
	box->time_to_die = (time_t)ft_atoi(argv[2]);
	box->time_to_eat = (time_t)ft_atoi(argv[3]);
	box->time_to_sleep = (time_t)ft_atoi(argv[4]);
	if (box->num_of_philo <= 0 || box->time_to_die <= 0 || \
		box->time_to_eat <= -1 || box->time_to_sleep <= -1)
		exit_with_err("Invalid range of arguments");
	if (argc == 6)
	{
		box->min_meal = (int)ft_atoi(argv[5]);
		if (box->min_meal <= 0)
			exit_with_err("Invalid value for minimum meal");
	}
}

void	set_table(t_box *box, int argc, char **argv)
{
	initiate_box(box);
	parse_args(argc, argv, box);
	box->philos = malloc(sizeof(t_philo) * box->num_of_philo);
	if (!box->philos)
		exit_with_err("malloc() has failed");
}
