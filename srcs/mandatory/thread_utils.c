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

int	initiate_philo_box(t_box *box)
{
	int	i;

	box->philos = (t_philo *)malloc(sizeof(t_philo) * box->num_of_philo);
	if (!box->philos)
		return (-1);
	box->simul_start = 0;
	i = 0;
	while (i < box->num_of_philo)
	{
		box->philos[i].idx = i;
		box->philos[i].box = box;
		box->philos[i].meal_cnt = 0;
		i++;
	}
	return (0);
}

int	create_philosophers(t_box *box)
{
	int	i;

	i = 0;
	while (i < box->num_of_philo)
	{
		if (pthread_create(&box->philos[i].tid, NULL, start_routine, \
			&box->philos[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	start_dining(t_box *box)
{
	int	i;

	box->simul_start = get_time_in_ms();
	if (box->simul_start == -1)
		return (-1);
	i = 0;
	while (i < box->num_of_philo)
		box->philos[i++].last_meal = box->simul_start;
	return (0);
}

int	wait_philos(t_box *box)
{
	int	i;

	i = 0;
	while (i < box->num_of_philo)
	{
		if (pthread_join(box->philos[i].tid, NULL))
			return (-1);
		i++;
	}
	return (0);
}
