/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:13:58 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 13:57:09 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	finish_meal(t_box *box, sem_t *sems[4])
{
	sem_close(sems[FORK]);
	sem_close(sems[PRINT]);
	sem_close(sems[MEAL]);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_MEAL_NAME);
	free(box->philos);
	box->philos = NULL;
}

void	initiate_semaphores(t_box *box, sem_t *sems[4])
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_MEAL_NAME);
	sems[FORK] = sem_open(SEM_FORK_NAME, O_CREAT, 0600, box->num_of_philo);
	sems[PRINT] = sem_open(SEM_PRINT_NAME, O_CREAT, 0600, 1);
	sems[MEAL] = sem_open(SEM_MEAL_NAME, O_CREAT, 0600, 0);
	if (sems[FORK] == SEM_FAILED || sems[PRINT] == SEM_FAILED \
		|| sems[MEAL] == SEM_FAILED)
	{
		finish_meal(box, sems);
		exit_with_err("failed to open semaphore");
	}
}
