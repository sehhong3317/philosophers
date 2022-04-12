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

int	check_vitality(int mode, t_info *info, int th_num)
{
	if (info->dead_philo >= 0)
	{
		unlock_mutexes(mode, info, th_num);
		print_philo_death(info);
		return (-1);
	}
	print_action(mode, info, th_num);
	return (0);
}

int	check_vitality_w_option(int mode, t_info *info, int th_num)
{
	if (info->dead_philo >= 0)
	{
		unlock_mutexes(mode, info, th_num);
		print_philo_death(info);
		return (-1);
	}
	if (info->meal_done)
	{
		unlock_mutexes(mode, info, th_num);
		return (-1);
	}
	print_action(mode, info, th_num);
	return (0);
}

static void	set_function_ptrs(t_info *info)
{
	if (info->num_of_meal != -1)
	{
		info->fptr = check_vitality_w_option;
		info->fptr2 = interval_usleep_w_option;
	}
	else
	{
		info->fptr = check_vitality;
		info->fptr2 = interval_usleep;
	}
}

void	*start_routine(void *arg)
{
	int		thd_num;
	t_philo	*philo;

	philo = (t_philo *)arg;
	thd_num = philo->thread_num;
	set_function_ptrs(philo->info);
	while (!philo->info->simul_start)
		;
	if (let_even_philos_run_behind(philo, thd_num) == -1)
		return (NULL);
	while (1)
	{
		if (takes_forks(philo->info, thd_num, philo->info->fptr) == -1)
			break ;
		if (eats(philo, thd_num, philo->info->fptr, philo->info->fptr2) == -1)
			break ;
		pthread_mutex_unlock(&philo->info->philos[thd_num].fork);
		pthread_mutex_unlock(&philo->info->philos[(thd_num + 1) % \
			philo->info->num_of_philo].fork);
		if (sleeps(philo, thd_num, philo->info->fptr, philo->info->fptr2) == -1)
			break ;
		if (philo->info->fptr(PHILO_THINKING, philo->info, thd_num) == -1)
			break ;
	}
	return (NULL);
}
