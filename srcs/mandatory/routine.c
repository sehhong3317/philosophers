/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:12:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/22 15:55:37 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	hold_even_philos(t_philo *philo)
{
	if ((philo->idx + 1) % 2 == 0)
	{
		if (set_time(philo->box, philo->box->time_to_eat / 3) == -1)
			return (-1);
	}
	return (0);
}

// idx에는 philo->idx가 들어감 (0부터 시작함)
int	eats_with_forks(t_philo *philo, int (*check_stat)(t_box *))
{
	if (check_stat(philo->box) > 0)
		return (-1);
	pthread_mutex_lock(philo->fork1);
	print_stat(philo, "\033[32mhas taken a fork\033[0m", FORK1);
	if (check_stat(philo->box) > 0)
		return (-2);
	pthread_mutex_lock(philo->fork2);
	print_stat(philo, "\033[32mhas taken a fork\033[0m", FORK2);
	if (check_stat(philo->box) > 0)
		return (-3);
	print_stat(philo, "\033[1;32mis eating\033[0m", EAT);
	if (set_time(philo->box, philo->box->time_to_eat) == -1)
		return (-3);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (0);
}

int	sleeps(t_philo *philo, int (*check_stat)(t_box *))
{
	if (check_stat(philo->box) > 0)
		return (-1);
	print_stat(philo, "\033[1;35mis sleeping\033[0m", SLEEP);
	if (set_time(philo->box, philo->box->time_to_sleep) == -1)
		return (-1);
	return (0);
}

int	thinks(t_philo *philo, int (*check_stat)(t_box *))
{
	if (check_stat(philo->box) > 0)
		return (-1);
	print_stat(philo, "\033[1;34mis thinking\033[0m", THINK);
	return (0);
}
