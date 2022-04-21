/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:24:09 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 21:31:40 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	t_err	call_philo(t_box *box, int idx)
{
	t_philo	*philo;

	pthread_mutex_lock(&(box->etc_lock));
	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (ERR_MALLOC);
	philo->idx = idx;
	philo->last_meal = 0;
	philo->meal_cnt = 0;
	philo->box = box;
	box->philos[idx] = philo;
	philo->fork1 = &(box->forks[idx]);
	philo->fork2 = &(box->forks[(idx + 1) % box->num_of_philo]);
	if (pthread_create(&(philo->tid), NULL, do_routine, philo))
	{
		pthread_mutex_unlock(&(box->etc_lock));
		return (ERR_THD_CREAT);
	}
	pthread_mutex_unlock(&(box->etc_lock));
	return (NO_ERR);
}

static	int	init_mutexes(t_box *box)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(box->etc_lock), NULL))
		return (-1);
	if (pthread_mutex_init(&(box->msg_lock), NULL))
		return (-1);
	while (i < box->num_of_philo)
	{
		if (pthread_mutex_init(&(box->forks[i++]), NULL))
			return (-1);
	}
	return (0);
}

t_err	call_philos(t_box *box)
{
	int		idx;
	t_err	ret;

	ret = 0;
	if (init_mutexes(box) == -1)
	{
		destroy_mutexes(box);
		free_philos(box, 0);
		return (ERR_MUTEX);
	}
	idx = 0;
	while (idx < box->num_of_philo)
	{	
		ret = call_philo(box, idx);
		if (ret != NO_ERR)
			break ;
		idx++;
	}
	if (ret != NO_ERR)
	{
		// TODO 좀 더 생각해보자.
		detach_philos(box, idx);
		destroy_mutexes(box);
		if (ret == ERR_THD_CREAT)
			idx++;
		free_philos(box, idx);
		return (ret);
	}
	return (NO_ERR);
}
