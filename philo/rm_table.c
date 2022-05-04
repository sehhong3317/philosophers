/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:30:47 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/04 21:28:04 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_box *box)
{
	int	i;

	if (box->min_meal > 0)
		pthread_mutex_destroy(&(box->eat_lock));
	pthread_mutex_destroy(&(box->msg_lock));
	// pthread_mutex_destroy(&(box->hold_lock));
	i = 0;
	while (i < box->num_of_philo)
		pthread_mutex_destroy(&(box->forks[i++]));
}

void	free_philos(t_box *box, int idx)
{
	int	i;

	i = -1;
	while (++i < idx)
	{
		if (box->philos[i])
		{
			free(box->philos[i]);
			box->philos[i] = NULL;
		}
	}
	if (box->philos)
	{
		free(box->philos);
		box->philos = NULL;
	}
	if (box->forks)
	{
		free(box->forks);
		box->forks = NULL;
	}
}

t_err	rm_table(t_box *box, int idx, t_err ret)
{
	destroy_mutexes(box);
	free_philos(box, idx);
	return (ret);
}
