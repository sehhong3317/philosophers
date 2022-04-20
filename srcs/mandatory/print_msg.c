/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:41:30 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/10 15:17:52 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_death(t_box *box)
{
	pthread_mutex_lock(&box->msg_lock);
	if (!box->death_msg)
	{
		printf("%ldms %d died\n", get_time_in_ms() - \
			box->simul_start, box->dead_philo + 1);
		box->death_msg = 1;
	}
	pthread_mutex_unlock(&box->msg_lock);
}

void	print_action(int mode, t_box *box, int th_num)
{
	pthread_mutex_lock(&box->msg_lock);
	if (mode == PHILO_FORK_1 || mode == PHILO_FORK_2)
		printf("%ldms %d has taken a fork\n", \
			get_time_in_ms() - box->simul_start, th_num + 1);
	else if (mode == PHILO_EATING)
		printf("%ldms %d is eating\n", \
			get_meal_time(&box->philos[th_num]), th_num + 1);
	else if (mode == PHILO_SLEEPING)
		printf("%ldms %d is sleeping\n", \
			get_time_in_ms() - box->simul_start, th_num + 1);
	else
		printf("%ldms %d is thinking\n", \
			get_time_in_ms() - box->simul_start, th_num + 1);
	pthread_mutex_unlock(&box->msg_lock);
}
