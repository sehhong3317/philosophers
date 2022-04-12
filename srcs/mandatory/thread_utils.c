/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:44:27 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/10 15:18:10 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initiate_philo_info(t_info *info)
{
	int	i;

	info->philos = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	if (!info->philos)
		return (-1);
	info->simul_start = 0;
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].thread_num = i;
		info->philos[i].info = info;
		info->philos[i].meal_count = 0;
		i++;
	}
	return (0);
}

int	create_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&info->philos[i].tid, NULL, start_routine, \
			&info->philos[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	start_dining(t_info *info)
{
	int	i;

	info->simul_start = get_time_in_ms();
	if (info->simul_start == -1)
		return (-1);
	i = 0;
	while (i < info->num_of_philo)
		info->philos[i++].last_meal = info->simul_start;
	return (0);
}

int	wait_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_join(info->philos[i].tid, NULL))
			return (-1);
		i++;
	}
	return (0);
}
