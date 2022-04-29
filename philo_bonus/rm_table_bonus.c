/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_table_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:30:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 13:42:16 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	delete_sems(t_box *box)
{
	sem_close(box->sem_fork);
	sem_unlink(FORK_NAME);
	sem_close(box->sem_print);
	sem_unlink(PRINT_NAME);
	sem_close(box->sem_meal);
	sem_unlink(MEAL_NAME);
	sem_close(box->sem_death);
	sem_unlink(DEATH_NAME);
	sem_close(box->sem_hold);
	sem_unlink(HOLD_NAME);
}

void	free_philos(t_box *box)
{
	if (box->philos)
	{
		free(box->philos);
		box->philos = NULL;
	}
	if (box)
	{
		free(box);
		box = NULL;
	}
}

void	kill_philos(t_box *box)
{
	int		i;
	pid_t	child_pid;

	i = 0;
	if (box->min_meal > 0 && box->pid_for_full)
		kill(box->pid_for_full, SIGINT);
	while (i < box->num_of_philo)
	{	
		child_pid = box->philos[i].pid;
		if (child_pid > 0)
			kill(child_pid, SIGINT);
		i++;
	}
}
