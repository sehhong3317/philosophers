/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 10:14:13 by sehhong           #+#    #+#             */
/*   Updated: 2022/02/22 13:06:33 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// keep monitoring the status of all philosophers
void	update_philo_status(t_info *info)
{
	int	(*fptr)(t_info *);

	if (info->num_of_meal == -1)
		fptr = update_philo_status_wo_option;
	else
		fptr = update_philo_status_w_option;
	while (1)
	{
		if (fptr(info) == -1)
			break ;
	}
}

// check if all the philosophers are alive or not
int	update_philo_status_wo_option(t_info *info)
{
	int		i;
	time_t	curr_time_in_ms;

	i = 0;
	curr_time_in_ms = get_time_in_ms();
	while (i < info->num_of_philo)
	{
		if (curr_time_in_ms - info->philos[i].last_meal > info->time_to_die)
		{
			info->dead_philo = i;
			// info->vital = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

// check if all the philosophers are alive 
// and if they finished their number of meal
int	update_philo_status_w_option(t_info *info)
{
	int	i;

	if (update_philo_status_wo_option(info) == -1)
		return (-1);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (info->philos[i].meal_count < info->num_of_meal)
			return (0);
		i++;
	}
	info->meal_done = 1;
	return (-1);
}
