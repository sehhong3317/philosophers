/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:01:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 14:04:15 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

void	print_eat(t_philo *philo)
{
	philo->last_meal = get_time();
	philo->meal_cnt++;
	sem_wait(philo->sems->sem_print);
	printf("%ld %d %s\n", philo->last_meal - philo->box->simul_start, \
	philo->idx, "\033[1;32mis eating\033[0m");
	if (philo->meal_cnt == philo->box->min_meal)
		sem_post(philo->sems->sem_meal);
	sem_post(philo->sems->sem_print);
}

void	print_stat(t_philo *philo, char *str)
{
	sem_wait(philo->sems->sem_print);
	printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
		philo->idx, str);
	sem_post(philo->sems->sem_print);
}

void	set_time(time_t time)
{
	time_t	target_time;

	target_time = get_time() + time;
	while (get_time() < target_time)
		usleep(100);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;

	ret = malloc(size * count);
	if (!ret)
		return (0);
	memset(ret, 0, count * size);
	return (ret);
}
