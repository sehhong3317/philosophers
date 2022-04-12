/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:03:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/13 00:03:33 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	initiate_box(t_box *box)
{
	box->num_of_philo = 0;
	box->time_to_die = 0;
	box->time_to_eat = -1;
	box->time_to_sleep = -1;
	box->min_meal = 0;
}

static	void	initiate_semaphore(t_box box)
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DEATH_NAME);
	sem_unlink(SEM_PRINT_NAME);
	box.sem_fork = sem_open(SEM_FORK_NAME, O_CREAT, 0600, box.num_of_philo);
	box.sem_death = sem_open(SEM_DEATH_NAME, O_CREAT, 0600, 0);
	box.sem_print = sem_open(SEM_PRINT_NAME, O_CREAT, 0600, 1);
	if (box.sem_fork < 0 || box.sem_death < 0 || box.sem_fork < 0)
		exit_with_err("failed to open semaphore");
}

void	set_table(t_box *box, int argc, char **argv)
{
	initiate_box(box);
	parse_arguments(argc, argv, box);
	box->philos = malloc(sizeof(t_philo) * box->num_of_philo);
	initiate_semaphore(*box);
}