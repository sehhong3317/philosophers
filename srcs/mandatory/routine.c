/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 16:12:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 15:29:46 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_only_one_case(t_box *box, int th_num)
{
	int	msg_count;

	msg_count = 0;
	while (1)
	{
		msg_count++;
		if (box->dead_philo >= 0)
		{
			pthread_mutex_unlock(&box->philos[th_num].fork);
			print_philo_death(box);
			break ;
		}
		if (msg_count == 1)
			print_action(PHILO_FORK_1, box, th_num);
	}
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

int	hold_even_philos(t_box *box, int idx)
{
	if ((idx + 1) % 2 == 0)
	{
		if (set_time(box->time_to_eat / 3, box) == -1)
			return (-1);
	}
	return (0);
}

// idx에는 philo->idx가 들어감 (0부터 시작함)
int	eats_with_forks(t_box *box, int idx)
{
	if (box->dead_philo > 0)
		return (-1);	//unlock 필요없음
	pthread_mutex_lock(&(box->philos[idx]->fork));
	print_stat(box->philos[idx], FORK1);
	if (box->dead_philo > 0)
		return (-2);	//포크 한개만 unlock
	// 포크 이름 미리 계산해서 입력해놓기
	pthread_mutex_lock(&(box->philos[(idx + 1) % box->num_of_philo]->fork));
	print_stat(box->philos[idx], FORK2);
	if (box->dead_philo > 0)
		return (-3);	//포크 두개 다 unlock
	print_stat(box->philos[idx], EAT);
	if (set_time(box->time_to_eat, box) == -1)
		return (-3);	//포크 두개 다 unlock
	pthread_mutex_unlock(&(box->philos[idx]->fork));
	pthread_mutex_unlock(&(box->philos[(idx + 1) % box->num_of_philo]->fork));
	return (0);
}

int	sleeps(t_box *box, int idx)
{
	if (box->dead_philo > 0)
		return (-1);	//unlock 필요없음
	print_stat(box->philos[idx], SLEEP);
	if (set_time(box->time_to_sleep, box) == -1)
		return (-1);	// unlock 필요없음
	return (0);
}

int	thinks(t_box *box, int idx)
{
	if (box->dead_philo > 0)
		return (-1);	//unlock 필요없음
	print_stat(box->philos[idx], THINK);
	return (0);
}

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

