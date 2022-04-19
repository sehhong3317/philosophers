/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_full_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:53:33 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 15:29:07 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	*monitor_if_all_full(void *arg)
{
	int		i;
	t_box 	*box;

	box = (t_box *)arg;
	i = -1;
	while (++i < box->num_of_philo)
		sem_wait(box->philos[0].sems[MEAL]);
	i = -1;
	while (++i < box->num_of_philo)
	{	
		printf("다음 pid를 죽인다: %d\n", box->philos[i].pid);
		kill(box->philos[i].pid, SIGINT);
	}
	return (NULL);
}

void	check_if_full(t_box *box)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, monitor_if_all_full, box);
	pthread_detach(tid);
}
