/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:23:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/22 10:14:50 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	main에서 아무리 죽은 이를 발견했다해도 보너스와 달리,
	thread를 죽일 수 없는 상황. 모든 행위를 할때마다,
	계속 dead_philo를 확인하고 안죽었으면 계속 돌고,
	죽었으면 이 thread를 여기서 끝내야함.
*/

void	*do_routine(void *arg)
{
	t_philo	*philo;
	int		ret;

	ret = 0;
	philo = (t_philo *)arg;
	while (!philo->last_meal)
		;
	if (hold_even_philos(philo) == -1)
		return (NULL);
	while (1)
	{
		ret = eats_with_forks(philo);
		if (ret < 0)
			break ;
		ret = sleeps(philo);
		if (ret < 0)
			break ;
		ret = thinks(philo);
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
