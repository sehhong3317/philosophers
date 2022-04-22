/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:33:16 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/22 12:54:40 by sehhong          ###   ########.fr       */
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
		if (box->dead_philo >= 0)
			return (-1);
	}
	return (0);
}

void	print_stat(t_philo *philo, char *stat, t_act action)
{
	t_box	*box;
	box = philo->box;
	pthread_mutex_lock(&(box->msg_lock));
	if (action == EAT)
	{
		philo->last_meal = get_time();
		philo->meal_cnt++;
		printf("%ld %d %s\n", philo->last_meal - box->simul_start, \
			(philo->idx) + 1, stat);
		if (box->min_meal > 0 && philo->meal_cnt == box->min_meal)
		{	
			box->meal_done--;
			printf("satisfied meal plan(%d)\n", philo->idx + 1);
		}
	}
	else
		printf("%ld %d %s\n", get_time() - box->simul_start, \
			(philo->idx) + 1, stat);
	pthread_mutex_unlock(&(box->msg_lock));
}
