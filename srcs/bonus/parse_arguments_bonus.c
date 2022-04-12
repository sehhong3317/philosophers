/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:25:05 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/12 14:19:53 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static	void	check_arg_range(t_box box)
{
	if (box.num_of_philo < 1 || box.time_to_die <= 0 ||
		box.time_to_eat < 0 || box.time_to_sleep < 0)
		exit_with_err("Invalid range of arguments");
}

static	void	check_min_meal(t_box *box, char *min_meal)
{
	box->min_meal = (int)ft_atoi(min_meal);
	if (box->min_meal < 1)
		exit_with_err("Invalid value assigned for the value \
			of \"number of times each philosopher must eat\"");
}


void	parse_arguments(int argc, char **argv, t_box *box)
{
	if (argc != 5 && argc != 6)
		exit_with_err("Invalid number of arguments");
	box->num_of_philo = (int)ft_atoi(argv[1]);
	box->time_to_die = (time_t)ft_atoi(argv[2]);
	box->time_to_eat = (time_t)ft_atoi(argv[3]);
	box->time_to_sleep = (time_t)ft_atoi(argv[4]);
	check_arg_range(*box);
	if (argc == 6)
		check_min_meal(box, argv[5]);
}