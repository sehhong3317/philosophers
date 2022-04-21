/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:44:27 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 21:23:14 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	if_all_alive(t_box *box)
{
	int		i;
	time_t	curr_time;

	i = -1;
	curr_time = get_time();
	while (++i < box->num_of_philo)
	{
		if (curr_time - box->philos[i]->last_meal > box->time_to_die)
		{
			// 여기서 바로 msg_lock 걸고 죽음메세지 내고 끝내는 게 낫지않음?
			if (box->dead_philo == -1)
			{
				pthread_mutex_lock(&(box->msg_lock));
				box->dead_philo = i;
				printf("%ld %d %s\n", curr_time - box->simul_start, \
					box->dead_philo + 1, "\033[31mis died\033[0m");
				pthread_mutex_unlock(&(box->msg_lock));
			}
			return (-1);
		}
	}
	return (0);
}

void	run_simulation(t_box *box)
{
	int	idx;

	idx = -1;
	pthread_mutex_lock(&(box->etc_lock));
	box->simul_start = get_time();
	while (++idx < box->num_of_philo)
		box->philos[idx]->last_meal = box->simul_start;
	pthread_mutex_unlock(&(box->etc_lock));
	while (1)
	{
		if (if_all_alive(box) == -1)
			return ;
	}
	idx = 0;
	while (idx < box->num_of_philo)
		pthread_join(box->philos[idx++]->tid, NULL);
}
