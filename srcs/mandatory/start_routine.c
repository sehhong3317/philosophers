/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:50:17 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/10 15:18:01 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_vitality(int mode, t_box *box, int th_num)
{
	if (box->dead_philo >= 0)
	{
		unlock_mutexes(mode, box, th_num);
		print_philo_death(box);
		return (-1);
	}
	print_action(mode, box, th_num);
	return (0);
}

int	check_vitality_w_option(int mode, t_box *box, int th_num)
{
	if (box->dead_philo >= 0)
	{
		unlock_mutexes(mode, box, th_num);
		print_philo_death(box);
		return (-1);
	}
	if (box->meal_done)
	{
		unlock_mutexes(mode, box, th_num);
		return (-1);
	}
	print_action(mode, box, th_num);
	return (0);
}

static void	set_function_ptrs(t_box *box)
{
	if (box->min_meal != -1)
	{
		box->fptr = check_vitality_w_option;
		box->fptr2 = interval_usleep_w_option;
	}
	else
	{
		box->fptr = check_vitality;
		box->fptr2 = interval_usleep;
	}
}

void	*start_routine(void *arg)
{
	int		thd_num;
	t_philo	*philo;

	philo = (t_philo *)arg;
	thd_num = philo->idx;
	set_function_ptrs(philo->box);
	while (!philo->box->simul_start)
		;
	if (let_even_philos_run_behind(philo, thd_num) == -1)
		return (NULL);
	while (1)
	{
		if (takes_forks(philo->box, thd_num, philo->box->fptr) == -1)
			break ;
		if (eats(philo, thd_num, philo->box->fptr, philo->box->fptr2) == -1)
			break ;
		pthread_mutex_unlock(&philo->box->philos[thd_num].fork);
		pthread_mutex_unlock(&philo->box->philos[(thd_num + 1) % \
			philo->box->num_of_philo].fork);
		if (sleeps(philo, thd_num, philo->box->fptr, philo->box->fptr2) == -1)
			break ;
		if (philo->box->fptr(PHILO_THINKING, philo->box, thd_num) == -1)
			break ;
	}
	return (NULL);
}
