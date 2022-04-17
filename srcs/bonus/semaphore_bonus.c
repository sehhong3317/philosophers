/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:13:58 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 17:17:00 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	finish_meal(t_box box, sem_t *sems[3])
{
	sem_close(sems[FORK]);
	sem_close(sems[DEATH]);
	sem_close(sems[PRINT]);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DEATH_NAME);
	sem_unlink(SEM_PRINT_NAME);
	free(box.philos);
	box.philos = NULL;
}

void	initiate_semaphores(t_box box, sem_t *sems[3])
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DEATH_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sems[FORK] = sem_open(SEM_FORK_NAME, O_CREAT, 0600, box.num_of_philo);
	sems[DEATH] = sem_open(SEM_DEATH_NAME, O_CREAT, 0600, 0);
	sems[PRINT] = sem_open(SEM_PRINT_NAME, O_CREAT, 0600, 1);
	if (sems[FORK] == SEM_FAILED || sems[DEATH] == SEM_FAILED || \
		sems[PRINT] == SEM_FAILED)
	{
		finish_meal(box, sems);
		exit_with_err("failed to open semaphore");
	}
}
