/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:33:16 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 20:12:00 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;

	ret = malloc(size * count);
	if (!ret)
		return (0);
	memset(ret, 0, count * size);
	return (ret);
}

time_t	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

int	set_time(t_box *box, time_t time)
{
	time_t	target_time;

	target_time = get_time() + time;
	while (get_time() < target_time)
	{
		usleep(100);
		if (box->dead_philo > 0)
			return (-1);
	}
	return (0);
}

void	print_stat(t_philo *philo, char *stat, t_act action)
{
	pthread_mutex_lock(&(philo->box->msg_lock));
	if (action == EAT)
	{
		philo->last_meal = get_time();
		philo->meal_cnt++;
		printf("%ld %d %s\n", philo->last_meal - philo->box->simul_start, \
			(philo->idx) + 1, stat);
	}
	else
		printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
			(philo->idx) + 1, stat);
	pthread_mutex_unlock(&(philo->box->msg_lock));
}

// time_t	get_meal_time(t_philo *philo)
// {
// 	time_t	meal_time_in_ms;

// 	meal_time_in_ms = get_time_in_ms();
// 	philo->last_meal = meal_time_in_ms;
// 	return (meal_time_in_ms - philo->box->simul_start);
// }

// int	interval_usleep(time_t interval, t_philo *philo, int mode, int th_num)
// {
// 	time_t	target_time;

// 	target_time = get_time_in_ms() + interval;
// 	while (get_time_in_ms() < target_time)
// 	{
// 		usleep(100);
// 		if (philo->box->dead_philo >= 0)
// 		{
// 			unlock_mutexes(mode, philo->box, th_num);
// 			print_philo_death(philo->box);
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }

// TODO 밥 먹을때 업데이트
// int	interval_usleep_w_option(time_t interval, t_philo *philo, int mode, \
// 	int th_num)
// {
// 	time_t	target_time;

// 	target_time = get_time_in_ms() + interval;
// 	while (get_time_in_ms() < target_time)
// 	{
// 		usleep(100);
// 		if (philo->box->dead_philo >= 0)
// 		{
// 			unlock_mutexes(mode, philo->box, th_num);
// 			print_philo_death(philo->box);
// 			return (-1);
// 		}
// 		if (philo->box->meal_done == 1)
// 		{
// 			unlock_mutexes(mode, philo->box, th_num);
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }
