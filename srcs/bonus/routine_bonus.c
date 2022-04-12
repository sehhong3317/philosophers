/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:57:19 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/13 00:47:01 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eats(t_box *box, int idx)
{
	sem_wait(box->sem_fork);
	printf("%ldms %d has taken a fork\n", \
		get_time_in_ms() - box->simul_start, idx + 1);
	sem_wait(box->sem_fork);
	printf("%ldms %d has taken a fork\n", \
		get_time_in_ms() - box->simul_start, idx + 1);
	// 먹는 과정 (메세지, 식사시간 업데이트, 시간재기)
	box->philos[idx].last_meal = get_time_in_ms();
	printf("%ldms %d is eating\n", \
		box->philos[idx].last_meal - box->simul_start, idx + 1);
	set_time(box->time_to_eat);
	sem_post(box->sem_fork);
	sem_post(box->sem_fork);
}

void	sleeps(t_box *box, int idx)
{
	sem_wait(box->sem_print);
	printf("%ldms %d is sleeping\n", \
		get_time_in_ms() - box->simul_start, idx + 1);
	set_time(box->time_to_sleep);
	sem_post(box->sem_print);
}

void	thinks(t_box *box, int idx)
{
	sem_wait(box->sem_print);
	printf("%ldms %d is thinking\n", \
		get_time_in_ms() - box->simul_start, idx + 1);
	sem_post(box->sem_print);
}