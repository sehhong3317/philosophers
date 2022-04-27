/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:26:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 22:07:46 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_sems(t_sems *sems)
{
	sem_close(sems->sem_fork);
	sem_unlink(FORK_NAME);
	sem_close(sems->sem_print);
	sem_unlink(PRINT_NAME);
	sem_close(sems->sem_meal);
	sem_unlink(MEAL_NAME);
	sem_close(sems->sem_death);
	sem_unlink(DEATH_NAME);
	sem_close(sems->sem_wait);
	sem_unlink(WAIT_NAME);
	sem_close(sems->sem_eat);
	sem_unlink(EAT_NAME);
}

void	free_philos(t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->num_of_philo)
	{
		if (box->philos[i])
		{
			free(box->philos[i]);
			box->philos[i] = NULL;
		}
	}
	if (box->philos)
	{
		free(box->philos);
		box->philos = NULL;
	}
}

void	exit_after_free(char *str, t_box *box, t_sems *sems)
{
	destroy_sems(sems);
	free_philos(box);
	exit_with_err(str);
}

void	kill_philos(t_box *box)
{
	int		i;
	pid_t	child_pid;

	i = 0;
	while (i < box->num_of_philo)
	{	
		child_pid = box->philos[i]->pid;
		if (child_pid > 0)
			kill(child_pid, SIGINT);
		i++;
	}
}

void	exit_after_kill(t_box *box, t_sems *sems)
{
	if (box->min_meal > 0)
		kill(box->pid_for_full, SIGINT);
	kill_philos(box);
	destroy_sems(sems);
	free_philos(box);
	exit_with_err("Failed to create thread");
}
