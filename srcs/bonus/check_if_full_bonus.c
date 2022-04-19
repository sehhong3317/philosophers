/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_full_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:53:33 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 16:05:03 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	*monitor_if_all_full(void *arg)
{
	int		i;
	t_box 	*box;

	box = (t_box *)arg;
	i = -1;
	printf("모니터: sem : %p\n", (int *)box->philos[0].sems[DEATH]);
	while (++i < box->num_of_philo)
		sem_wait(box->philos[0].sems[MEAL]);
	sem_post(box->philos[0].sems[DEATH]);
	return (NULL);
}

void	check_if_full(t_box *box)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, monitor_if_all_full, box);
	pthread_detach(tid);
}
