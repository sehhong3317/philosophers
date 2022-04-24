/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:23:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/24 17:13:10 by sehhong          ###   ########.fr       */
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

int	hold_even_philos(t_philo *philo)
{
	if ((philo->idx + 1) % 2 == 0)
		set_time(philo->box->time_to_eat / 3);
	return (0);
}

void	*do_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->last_meal)
		;
	if (hold_even_philos(philo) == -1)
		return (NULL);
	while (!check_stat(philo->box))
	{
		pthread_mutex_lock(philo->fork1);
		print_stat(philo, "\033[33mhas taken a fork\033[0m");
		if (philo->box->num_of_philo == 1)
			return (NULL);
		pthread_mutex_lock(philo->fork2);
		print_stat(philo, "\033[33mhas taken a fork\033[0m");
		philo_eat(philo);
		set_time(philo->box->time_to_eat);
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		print_stat(philo, "\033[35mis sleeping\033[0m");
		set_time(philo->box->time_to_sleep);
		print_stat(philo, "\033[34mis thinking\033[0m");
	}
	return (NULL);
}
