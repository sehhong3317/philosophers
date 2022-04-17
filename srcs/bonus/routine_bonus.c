/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:57:19 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 08:40:19 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	print_stat(t_philo philo, char *str)
{
	printf("%ldms %d %s\n", get_time_in_ms() - philo.box->simul_start, \
		philo.philo_num, str);
}

void	do_routine(t_philo philo)
{
	sem_wait(philo.box->sem_fork);
	print_stat(philo, "has taken a fork");
	sem_wait(philo.box->sem_fork);
	print_stat(philo, "has taken a fork");
	philo.last_meal = get_time_in_ms();
	print_stat(philo, "is eating");
	set_time(philo.box->time_to_eat);
	sem_post(philo.box->sem_fork);
	sem_post(philo.box->sem_fork);
	print_stat(philo, "is sleeping");
	set_time(philo.box->time_to_sleep);
	print_stat(philo, "is thinking");
}