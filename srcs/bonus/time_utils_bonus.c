/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:01:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/12 19:06:00 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time_in_ms(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL ) == -1)
		exit_with_err("gettimeofday() has failed");
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

// time_t	update_meal_time(t_philo *philo)
// {
// 	time_t	meal_time_in_ms;

// 	meal_time_in_ms = get_time_in_ms();
// 	philo->last_meal = meal_time_in_ms();
// 	return (meal_time_in_ms - philo->)
// }