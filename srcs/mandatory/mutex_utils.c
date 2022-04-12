/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:44:57 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/10 15:17:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initiate_mutex(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->msg_lock, NULL))
		return (-1);
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->philos[i].fork, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	destroy_mutex(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&info->msg_lock))
		return (-1);
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_destroy(&info->philos[i].fork))
			return (-1);
		i++;
	}
	return (0);
}

void	unlock_mutexes(int mode, t_info *info, int th_num)
{
	if (mode == PHILO_FORK_1 || mode == PHILO_FORK_2 \
		|| mode == PHILO_EATING)
	{
		pthread_mutex_unlock(&info->philos[th_num].fork);
		if (mode != PHILO_FORK_1)
			pthread_mutex_unlock(&info->philos[(th_num + 1) % \
				info->num_of_philo].fork);
	}
}
