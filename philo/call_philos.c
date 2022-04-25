/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:24:09 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 11:54:26 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	t_err	prepare_philo(t_box *box, int idx)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (ERR_MALLOC);
	philo->idx = idx;
	philo->box = box;
	box->philos[idx] = philo;
	philo->fork1 = &(box->forks[idx]);
	philo->fork2 = &(box->forks[(idx + 1) % box->num_of_philo]);
	return (NO_ERR);
}

static	t_err	rm_table_if_err(t_box *box, int idx, t_err ret)
{
	if (ret == ERR_THD_CREAT)
		detach_philos(box, idx);
	destroy_mutexes(box);
	if (ret == ERR_THD_CREAT)
		idx = box->num_of_philo;
	free_philos(box, idx);
	return (ret);
}

static	t_err	call_philo(t_box *box, int idx)
{
	t_philo	*philo;

	philo = box->philos[idx];
	pthread_mutex_lock(&(box->lock));
	if (pthread_create(&(philo->tid), NULL, do_routine, philo))
	{
		pthread_mutex_unlock(&(box->lock));
		return (ERR_THD_CREAT);
	}
	pthread_mutex_unlock(&(box->lock));
	return (NO_ERR);
}

t_err	call_philos(t_box *box)
{
	int		idx;
	t_err	ret;

	idx = -1;
	while (++idx < box->num_of_philo)
	{
		ret = prepare_philo(box, idx);
		if (ret == ERR_MALLOC)
			return (rm_table_if_err(box, idx, ret));
	}
	idx = -1;
	while (++idx < box->num_of_philo)
	{	
		ret = call_philo(box, idx);
		if (ret == ERR_THD_CREAT)
			return (rm_table_if_err(box, idx, ret));
	}
	return (NO_ERR);
}
