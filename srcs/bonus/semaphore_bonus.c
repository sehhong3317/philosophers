/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:13:58 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 15:52:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	free(box->philos);
	box->philos = NULL;
}

static	void	check_sem_open(t_box *box, t_sems *sems, sem_t *sem)
{
	if (sem == SEM_FAILED)
	{
		finish_meal(box, sems);
		exit_with_err("Failed to call sem_open()");
	}
}

void	initiate_semaphores(t_box *box, t_sems *sems)
{
	sem_unlink(SEM_FORK_NAME);
	sems->sem_fork = sem_open(SEM_FORK_NAME, O_CREAT, 0600, box->num_of_philo);
	check_sem_open(box, sems, sems->sem_fork);
	sem_unlink(SEM_PRINT_NAME);
	sems->sem_print = sem_open(SEM_PRINT_NAME, O_CREAT, 0600, 1);
	check_sem_open(box, sems, sems->sem_print);
	sem_unlink(SEM_MEAL_NAME);
	sems->sem_meal = sem_open(SEM_MEAL_NAME, O_CREAT, 0600, 0);
	check_sem_open(box, sems, sems->sem_meal);
	sem_unlink(SEM_DEATH_NAME);
	sems->sem_death = sem_open(SEM_DEATH_NAME, O_CREAT, 0600, 0);
	check_sem_open(box, sems, sems->sem_death);
}
