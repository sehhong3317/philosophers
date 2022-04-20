/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:35:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 17:33:11 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static	void	fill_up_box(t_box *box, char **argv)
{
	box->min_meal = 0;
	box->simul_start = 0;
	box->dead_philo = -1;
	box->death_msg = 0;
	box->meal_done = 0;
	box->philos = (t_philo **)ft_calloc(box->num_of_philo, sizeof(t_philo *));
	box->num_of_philo = (int)ft_atoi(argv[1]);
	box->time_to_die = (time_t)ft_atoi(argv[2]);
	box->time_to_eat = (time_t)ft_atoi(argv[3]);
	box->time_to_sleep = (time_t)ft_atoi(argv[4]);
}

t_err	set_table(int argc, char **argv, t_box *box)
{
	if (argc != 5 && argc != 6)
		return (ERR_ARG);
	fill_up_box(box, argv);
	if (!box->philos)
		return (ERR_MALLOC);
	if (box->num_of_philo < 1 || box->time_to_die <= 0 \
		|| box->time_to_eat < 0 || box->time_to_sleep < 0)
		return (ERR_ARG);
	if (argc == 6)
	{	
		box->min_meal = (int)ft_atoi(argv[5]);
		if (box->min_meal <= 0)
			return (ERR_ARG);
	}
	return (NO_ERR);
}
