/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:23:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/23 10:06:11 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	main에서 아무리 죽은 이를 발견했다해도 보너스와 달리,
	thread를 죽일 수 없는 상황. 모든 행위를 할때마다,
	계속 dead_philo를 확인하고 안죽었으면 계속 돌고,
	죽었으면 이 thread를 여기서 끝내야함.
*/

static	int	check_stat_wo_opt(t_box *box)
{
	if (box->dead_philo >= 0)
		return (1);
	return (0);
}

static	int	check_stat_w_opt(t_box *box)
{
	if (box->dead_philo >= 0)
		return (1);
	if (!box->meal_done)
		return (1);
	return (0);
}

static	int	(*how_to_check_stat(int min_meal))(t_box *box)
{
	if (min_meal > 0)
		return (check_stat_w_opt);
	return (check_stat_wo_opt);
}

static	void	unlock_mutex_if_err(t_philo *philo, int ret)
{
	if (ret <= -2)
	{
		if (ret == -3)
			pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
	}
}

void	*do_routine(void *arg)
{
	t_philo	*philo;
	int		ret;
	int		(*check_stat)(t_box *box);

	ret = 0;
	philo = (t_philo *)arg;
	check_stat = how_to_check_stat(philo->box->min_meal);
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
	unlock_mutex_if_err(philo, ret);
	return (NULL);
}
