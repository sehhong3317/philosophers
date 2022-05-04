/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:42:05 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/04 21:28:10 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	init_mutexes(t_box *box)
{
	int	i;

	i = 0;
	if (box->min_meal > 0 && pthread_mutex_init(&(box->eat_lock), NULL))
		return (-1);
	// if (pthread_mutex_init(&(box->hold_lock), NULL))
	// 	return (-1);
	if (pthread_mutex_init(&(box->msg_lock), NULL))
		return (-1);
	while (i < box->num_of_philo)
	{
		if (pthread_mutex_init(&(box->forks[i++]), NULL))
			return (-1);
	}
	return (0);
}

static	int	prepare_philo(t_box *box, int idx)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (-1);
	philo->idx = idx;
	philo->box = box;
	philo->fork1 = &(box->forks[idx]);
	philo->fork2 = &(box->forks[(idx + 1) % box->num_of_philo]);
	box->philos[idx] = philo;
	return (0);
}

t_err	set_table(t_box *box)
{
	int		idx;

	if (init_mutexes(box) == -1)
		return (rm_table(box, 0, ERR_MUTEX));
	idx = -1;
	while (++idx < box->num_of_philo)
	{
		if (prepare_philo(box, idx) == -1)
			return (rm_table(box, idx, ERR_MALLOC));
	}
	return (NO_ERR);
}
