/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:14:26 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 17:19:07 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

time_t	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

time_t	get_meal_time(t_philo *philo)
{
	time_t	meal_time_in_ms;

	meal_time_in_ms = get_time_in_ms();
	philo->last_meal = meal_time_in_ms;
	return (meal_time_in_ms - philo->box->simul_start);
}

int	interval_usleep(time_t interval, t_philo *philo, int mode, int th_num)
{
	time_t	target_time;

	target_time = get_time_in_ms() + interval;
	while (get_time_in_ms() < target_time)
	{
		usleep(100);
		if (philo->box->dead_philo >= 0)
		{
			unlock_mutexes(mode, philo->box, th_num);
			print_philo_death(philo->box);
			return (-1);
		}
	}
	return (0);
}

int	interval_usleep_w_option(time_t interval, t_philo *philo, int mode, \
	int th_num)
{
	time_t	target_time;

	target_time = get_time_in_ms() + interval;
	while (get_time_in_ms() < target_time)
	{
		usleep(100);
		if (philo->box->dead_philo >= 0)
		{
			unlock_mutexes(mode, philo->box, th_num);
			print_philo_death(philo->box);
			return (-1);
		}
		if (philo->box->meal_done == 1)
		{
			unlock_mutexes(mode, philo->box, th_num);
			return (-1);
		}
	}
	return (0);
}
