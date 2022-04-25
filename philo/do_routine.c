/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:23:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 14:03:48 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stat(t_box *box)
{
	if (box->dead_philo >= 0)
		return (1);
	if (box->min_meal > 0 && !box->meal_done)
		return (1);
	return (0);
}

static	void	hold_even_philos(t_philo *philo)
{
	if ((philo->idx + 1) % 2 == 0)
		set_time(philo->box->time_to_eat / 3);
}

static	int	routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	if (print_stat(philo, "\033[33mhas taken a fork\033[0m") == -1)
		return (-2);
	if (philo->box->num_of_philo == 1)
		return (-2);
	pthread_mutex_lock(philo->fork2);
	if (print_stat(philo, "\033[33mhas taken a fork\033[0m") == -1)
		return (-3);
	if (print_eat(philo) == -1)
		return (-3);
	set_time(philo->box->time_to_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	if (print_stat(philo, "\033[35mis sleeping\033[0m") == -1)
		return (-1);
	set_time(philo->box->time_to_sleep);
	if (print_stat(philo, "\033[34mis thinking\033[0m") == -1)
		return (-1);
	return (0);
}

static	void	unlock_mutex_if_err(t_philo *philo, int ret)
{
	if (ret <= -2)
	{
		if (ret == -3)
			pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
	}
}

void	*do_routine(void *arg)
{
	t_philo	*philo;
	int		ret;

	ret = 0;
	philo = (t_philo *)arg;
	while (!philo->last_meal)
		;
	hold_even_philos(philo);
	while (!check_stat(philo->box))
	{
		ret = routine(philo);
		if (ret < 0)
			break ;
	}
	unlock_mutex_if_err(philo, ret);
	return (NULL);
}
