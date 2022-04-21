/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:24:09 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 17:44:46 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	main에서 아무리 죽은 이를 발견했다해도 보너스와 달리,
	thread를 죽일 수 없는 상황. 모든 행위를 할때마다,
	계속 dead_philo를 확인하고 안죽었으면 계속 돌고,
	죽었으면 이 thread를 여기서 끊어내야함.
*/
static	void	do_routine(void *arg)
{
	t_philo	*philo;
	int		ret;
	int		idx;
	t_box	*box;

	ret = 0;
	philo = (t_philo *)arg;
	idx = philo->idx;
	box = philo->box;
	while (!philo->last_meal)
		;
	if (hold_even_philos(box, idx) == -1)
		return (NULL);
	while (1)
	{
		ret = eats_with_fork(philo->box, idx);
		if (ret < 0)
			break ;
		ret = sleeps(philo->box, idx);
		if (ret < 0)
			break ;
		ret = thinks(philo->box, idx);
		if (ret < 0)
			break ;
	}
	if (ret <= -2)
	{
		if (ret == -3)
			pthread_mutex_unlock(&(box->philos[(idx + 1) \
				% box->num_of_philo]->fork));
		pthread_mutex_unlock(&(box->philos[idx]->fork));
	}
	return (NULL);
}

// static	void	do_routine_w_meal()
// {

// }

// TODO mutex필요
static	t_err	call_philo(t_box *box, int idx)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (ERR_MALLOC);
	philo->idx = idx;
	philo->last_meal = 0;
	philo->meal_cnt = 0;
	philo->box = box;
	if (pthread_create(&(philo->tid), NULL, do_routine, philo))
		return (ERR_THD_CREAT);
	return (NO_ERR);
}

int	init_mutexes(t_box *box)
{
	int	i;
	
	i = 0;
	if (pthread_mutex_init(&(box->etc_lock), NULL))
		return (-1);
	if (pthread_mutex_init(&(box->msg_lock), NULL))
		return (-1);
	while (i < box->num_of_philo)
	{
		if (pthread_mutex_init(&(box->forks[i++]), NULL))
			return (-1);
	}
	return (0);
}

// TODO mutex 필요? -> 질문하기
t_err	call_philos(t_box *box)
{
	int		idx;
	t_err	ret;

	ret = 0;
	if (init_mutexes(box) == -1)
	{
		destroy_mutexes(box);
		free_philos(box, 0);
		return (ERR_MUTEX);
	}
	idx = 0;
	while (idx < box->num_of_philo)
	{	
		ret = call_philo(box, idx);
		if (ret != NO_ERR)
			break ;
		idx++;
	}
	if (ret != NO_ERR)
	{
		detach_philos(box, idx);
		destroy_mutexes(box);
		if (ret == ERR_THD_CREAT)
			idx++;
		free_philos(box, idx);
		return (ret);
	}
	return (NO_ERR);
}
