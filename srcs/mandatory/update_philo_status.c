/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:14:13 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 20:04:34 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	update_philo_status(t_box *box)
// {
// 	int	(*fptr)(t_box *);

// 	if (box->min_meal == -1)
// 		fptr = update_philo_status_wo_option;
// 	else
// 		fptr = update_philo_status_w_option;
// 	while (1)
// 	{
// 		if (fptr(box) == -1)
// 			break ;
// 	}
// }

// int	update_philo_status_wo_option(t_box *box)
// {
// 	int		i;
// 	time_t	curr_time_in_ms;

// 	i = 0;
// 	curr_time_in_ms = get_time_in_ms();
// 	while (i < box->num_of_philo)
// 	{
// 		if (curr_time_in_ms - box->philos[i].last_meal > box->time_to_die)
// 		{
// 			box->dead_philo = i;
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// TODO 밥먹을때 업데이트
// int	update_philo_status_w_option(t_box *box)
// {
// 	int	i;

// 	if (update_philo_status_wo_option(box) == -1)
// 		return (-1);
// 	i = 0;
// 	while (i < box->num_of_philo)
// 	{
// 		if (box->philos[i].meal_cnt < box->min_meal)
// 			return (0);
// 		i++;
// 	}
// 	box->meal_done = 1;
// 	return (-1);
// }
