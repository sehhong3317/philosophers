/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:30:47 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 16:52:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_philos(t_box *box, int idx)
{
	int	i;

	i = -1;
	while (++i < idx)
		pthread_detach(box->philos[i]->tid);
}

void	destroy_mutexes(t_box *box)
{
	int	i;

	pthread_mutex_destroy(&(box->etc_lock));
	pthread_mutex_destroy(&(box->msg_lock));
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

void	rm_table(t_box *box)
{
	destroy_mutex(box, box->num_of_philo);
	free_philos(box, box->num_of_philo);
}
