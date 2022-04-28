/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:31:33 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 01:36:10 by sehhong          ###   ########.fr       */
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

static	void	parse_args(int argc, char **argv, t_box *box)
{
	box->num_of_philo = (int)ft_atoi(argv[1]);
	box->time_to_die = (time_t)ft_atoi(argv[2]);
	box->time_to_eat = (time_t)ft_atoi(argv[3]);
	box->time_to_sleep = (time_t)ft_atoi(argv[4]);
	if (box->num_of_philo < 1 || box->time_to_die <= 0 || \
			box->time_to_eat < 0 || box->time_to_sleep < 0)
		exit_with_err("Invalid value of argument");
	if (argc == 6)
	{
		box->min_meal = (int)ft_atoi(argv[5]);
		if (box->min_meal <= 0)
			exit_with_err("Invalid value for the minimum number of meal");
	}
}

static	void	init_sems(t_box *box)
{
	sem_unlink(FORK_NAME);
	box->sem_fork = sem_open(FORK_NAME, O_CREAT, 0600, box->num_of_philo);
	sem_unlink(PRINT_NAME);
	box->sem_print = sem_open(PRINT_NAME, O_CREAT, 0600, 1);
	sem_unlink(MEAL_NAME);
	box->sem_meal = sem_open(MEAL_NAME, O_CREAT, 0600, 0);
	sem_unlink(DEATH_NAME);
	box->sem_death = sem_open(DEATH_NAME, O_CREAT, 0600, 0);
	sem_unlink(CALL_NAME);
	box->sem_hold = sem_open(CALL_NAME, O_CREAT, 0600, 1);
	if (box->sem_fork == SEM_FAILED || box->sem_print == SEM_FAILED || \
		box->sem_meal == SEM_FAILED || box->sem_death == SEM_FAILED || \
		box->sem_hold == SEM_FAILED)
		exit_after_free("Failed to call sem_open()", box);
}

static	void	prepare_philos(t_box *box)
{
	int	i;

	box->philos = (t_philo *)ft_calloc(box->num_of_philo, sizeof(t_philo));
	if (!box->philos)
		exit_with_err("Failed to call malloc()");
	i = 0;
	while (i < box->num_of_philo)
	{
		box->philos[i].idx = i;
		box->philos[i].box = box;
		i++;
	}
}

t_box	*set_table(int argc, char **argv)
{
	t_box	*box;

	box = (t_box *)malloc(sizeof(t_box));
	if (!box)
		exit_with_err("Failed to call malloc()");
	parse_args(argc, argv, box);
	init_sems(box);
	prepare_philos(box);
	return (box);
}
