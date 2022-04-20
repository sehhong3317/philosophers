/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:26:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 11:27:45 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_with_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(STDERR_FILENO, str, i);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	finish_meal(t_box *box, t_sems *sems)
{
	int	i;

	sem_close(sems->sem_fork);
	sem_close(sems->sem_print);
	sem_close(sems->sem_meal);
	sem_close(sems->sem_death);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_MEAL_NAME);
	sem_unlink(SEM_DEATH_NAME);
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
	finish_meal(box, sems);
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
		if (child_pid)
			kill(child_pid, SIGINT);
		i++;
	}
}

void	exit_after_kill(t_box *box, t_sems *sems)
{
	kill_philos(box);
	finish_meal(box, sems);
	exit_with_err("Failed to create thread");
}
