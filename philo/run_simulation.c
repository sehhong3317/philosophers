/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:24:09 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 15:20:41 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	call_philos(t_box *box)
{
	t_philo	*philo;
	int		thd_cnt;
	int		idx;

	thd_cnt = 0;
	idx = -1;
	pthread_mutex_lock(&(box->wait_lock));
	while (++idx < box->num_of_philo)
	{	
		philo = box->philos[idx];
		if (pthread_create(&(philo->tid), NULL, do_routine, philo))
			break ;
		thd_cnt++;
	}
	if (thd_cnt == box->num_of_philo)
		box->alert = ALL_ALIVE;
	pthread_mutex_unlock(&(box->wait_lock));
	return (thd_cnt);
}

t_err	run_simulation(t_box *box)
{
	int	thd_cnt;
	int	idx;

	thd_cnt = call_philos(box);
	idx = -1;
	pthread_mutex_lock(&(box->wait_lock));
	box->simul_start = get_time();
	while (++idx < box->num_of_philo)
		box->philos[idx]->last_meal = box->simul_start;
	pthread_mutex_unlock(&(box->wait_lock));
	if (thd_cnt < box->num_of_philo)
	{
		idx = -1;
		while (++idx < thd_cnt)
			pthread_join(box->philos[idx]->tid, NULL);
		rm_table(box, box->num_of_philo, ERR_THD_CREAT);
	}
	return (NO_ERR);
}
