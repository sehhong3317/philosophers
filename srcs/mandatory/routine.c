/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:12:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 21:34:32 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO 철학자 한명일때? 향후 추가
// static void	philo_only_one_case(t_box *box, int th_num)
// {
// 	int	msg_count;

// 	msg_count = 0;
// 	while (1)
// 	{
// 		msg_count++;
// 		if (box->dead_philo >= 0)
// 		{
// 			pthread_mutex_unlock(&box->philos[th_num].fork);
// 			print_philo_death(box);
// 			break ;
// 		}
// 		if (msg_count == 1)
// 			print_action(PHILO_FORK_1, box, th_num);
// 	}
// }

int	hold_even_philos(t_philo *philo)
{
	if ((philo->idx + 1) % 2 == 0)
	{
		if (set_time(philo->box, philo->box->time_to_eat / 3) == -1)
			return (-1);
	}
	return (0);
}

// idx에는 philo->idx가 들어감 (0부터 시작함)
int	eats_with_forks(t_philo *philo)
{
	if (philo->box->dead_philo > 0)
		return (-1);
	pthread_mutex_lock(philo->fork1);
	print_stat(philo, "\033[1;32mhas taken a fork\033[0m", FORK1);
	if (philo->box->dead_philo > 0)
		return (-2);
	pthread_mutex_lock(philo->fork2);
	print_stat(philo, "\033[1;32mhas taken a fork\033[0m", FORK2);
	if (philo->box->dead_philo > 0)
		return (-3);
	print_stat(philo, "\033[32mis eating\033[0m", EAT);
	if (set_time(philo->box, philo->box->time_to_eat) == -1)
		return (-3);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (0);
}

int	sleeps(t_philo *philo)
{
	if (philo->box->dead_philo > 0)
		return (-1);
	print_stat(philo, "\033[1;35mis sleeping\033[0m", SLEEP);
	if (set_time(philo->box, philo->box->time_to_sleep) == -1)
		return (-1);
	return (0);
}

int	thinks(t_philo *philo)
{
	if (philo->box->dead_philo > 0)
		return (-1);
	print_stat(philo, "\033[1;34mis thinking\033[0m", THINK);
	return (0);
}

// int	let_even_philos_run_behind(t_philo *philo, int idx)
// {
// 	if ((idx + 1) % 2 == 0)
// 	{
// 		if (interval_usleep(philo->box->time_to_eat / 3, philo, \
// 			PHILO_WAIT, idx) == -1)
// 		{
// 			print_philo_death(philo->box);
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }

// int	sleeps(t_philo *philo, int th_num, int (*fptr)(int, t_box *, int), \
// 	int (*fptr2)(time_t, t_philo *, int, int))
// {
// 	if (fptr(PHILO_SLEEPING, philo->box, th_num))
// 		return (-1);
// 	if (fptr2(philo->box->time_to_sleep, philo, \
// 		PHILO_SLEEPING, th_num))
// 		return (-1);
// 	return (0);
// }
// int	takes_forks(t_box *box, int th_num, int (*fptr)(int, t_box *, int))
// {
// 	if (box->dead_philo >= 0)
// 	{
// 		print_philo_death(box);
// 		return (-1);
// 	}
// 	pthread_mutex_lock(&box->philos[th_num].fork);
// 	if (box->num_of_philo == 1)
// 	{	
// 		philo_only_one_case(box, th_num);
// 		return (-1);
// 	}
// 	if (fptr(PHILO_FORK_1, box, th_num) == -1)
// 		return (-1);
// 	pthread_mutex_lock(&box->philos[(th_num + 1) % \
// 		box->num_of_philo].fork);
// 	if (fptr(PHILO_FORK_2, box, th_num) == -1)
// 		return (-1);
// 	return (0);
// }

// int	eats(t_philo *philo, int th_num, int (*fptr)(int, t_box *, int), \
// 	int (*fptr2)(time_t, t_philo *, int, int))
// {
// 	if (fptr(PHILO_EATING, philo->box, th_num) == -1)
// 		return (-1);
// 	if (fptr2(philo->box->time_to_eat, philo, PHILO_EATING, \
// 		th_num) == -1)
// 		return (-1);
// 	if (philo->box->min_meal >= 0)
// 		philo->meal_cnt++;
// 	return (0);
// }
