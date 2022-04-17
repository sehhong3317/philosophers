/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:01:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 08:40:01 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL ) == -1)
		exit_with_err("gettimeofday() has failed");
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

void	set_time(time_t time)
{
	time_t	target_time;

	target_time = get_time() + time;
	while (get_time() < target_time)
		usleep(100);
}