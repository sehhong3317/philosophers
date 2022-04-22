/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:23:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/22 10:06:03 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	main에서 아무리 죽은 이를 발견했다해도 보너스와 달리,
	thread를 죽일 수 없는 상황. 모든 행위를 할때마다,
	계속 dead_philo를 확인하고 안죽었으면 계속 돌고,
	죽었으면 이 thread를 여기서 끝내야함.
*/

static	int	check_stat_wo_opt(t_philo *philo)
{
	if (philo->box->dead_philo >= 0)
		return (1);
	return (0);
}

static	int	check_stat_w_opt(t_philo *philo)
{
	if (philo->box->dead_philo >= 0)
		return (1);
	if (!philo->box->meal_done)
		return (1);
	return (0);
}

// static	int	(*is_meal_option(int min_meal))(t_philo *)
// {
// 	if (min_meal > 0)
// 		return (check_stat_wo_opt);
// 	return (check_stat_w_opt);
// }

void	*do_routine(void *arg)
{
	t_philo	*philo;
	int		ret;
	int		(*check_stat)(t_philo *philo);

	ret = 0;
	philo = (t_philo *)arg;
	// check_stat = is_meal_option(philo->box->min_meal);
	if (philo->box->min_meal > 0)
		check_stat = check_stat_wo_opt;
	else
		check_stat = check_stat_w_opt;
	while (!philo->last_meal)
		;
	if (hold_even_philos(philo) == -1)
		return (NULL);
	while (1)
	{
		ret = eats_with_forks(philo, check_stat);
		if (ret < 0)
			break ;
		ret = sleeps(philo, check_stat);
		if (ret < 0)
			break ;
		ret = thinks(philo, check_stat);
		if (ret < 0)
			break ;
	}
	if (ret <= -2)
	{
		if (ret == -3)
			pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
	}
	return (NULL);
}

/*
int add(int a, int b)    // int형 반환값, int형 매개변수 두 개
{
    return a + b;
}

int (*getAdd(int x, int y))(int, int)

int (*getAdd())(int, int)    // 함수 포인터를 반환값으로 지정
{
    return add;    // add 함수의 메모리 주소를 반환
}
*/