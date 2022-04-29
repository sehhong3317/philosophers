/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 08:44:27 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 12:18:47 by sehhong          ###   ########.fr       */
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
			if (box->alert == ALL_ALIVE)
			{
				pthread_mutex_lock(&(box->msg_lock));
				box->alert = PHILO_DEAD;
				printf("%ld %d %s\n", curr_time - box->simul_start, \
					i + 1, "\033[1;31mdied\033[0m");
				pthread_mutex_unlock(&(box->msg_lock));
			}
			return (-1);
		}
	}
	return (0);
}

void	monitor_philos(t_box *box)
{
	int	idx;

	while (1)
	{
		if (if_all_alive(box) == -1)
			break ;
		if (box->min_meal > 0 && !box->meal_done)
			break ;
		usleep(100);
	}
	idx = 0;
	while (idx < box->num_of_philo)
		pthread_join(box->philos[idx++]->tid, NULL);
	rm_table(box, box->num_of_philo, NO_ERR);
}
