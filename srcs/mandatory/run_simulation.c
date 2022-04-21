/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:44:27 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 15:36:55 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO mutex 필요
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
			if (box->dead_philo == -1)
				box->dead_philo = i + 1;
			// 여기서 바로 msg_lock 걸고 죽음메세지 내고 끝내는 게 낫지않음?
			return (-1);
		}
	}
	return (0);
}

// TODO mutex 필요
void	run_simulation(t_box *box)
{
	int	idx;

	box->simul_start = get_time();
	idx = 0;
	while (idx < box->num_of_philo)
		box->philos[idx++]->last_meal = box->simul_start;
	while (1)
	{
		if (if_all_alive(box) == -1)
			return ;
	}
	idx = 0;
	while (idx < box->num_of_philo)
		pthread_join(box->philos[idx++]->tid, NULL);
}
