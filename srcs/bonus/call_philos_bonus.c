/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 08:40:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 17:04:09 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	do_routine(t_philo *philo)
{
	sem_wait(philo->sems[FORK]);
	print_stat(*philo, "has taken a fork");
	sem_wait(philo->sems[FORK]);
	print_stat(*philo, "has taken a fork");
	philo->last_meal = get_time();
	print_stat(*philo, "is eating");
	set_time(philo->box->time_to_eat);
	sem_post(philo->sems[FORK]);
	sem_post(philo->sems[FORK]);
	print_stat(*philo, "is sleeping");
	set_time(philo->box->time_to_sleep);
	print_stat(*philo, "is thinking");
}

static	void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((get_time() - philo->last_meal) < philo->box->time_to_die)
		;
	print_stat(*philo, "is died");
	sem_post(philo->sems[DEATH]);
	return (NULL);
}

static	void	call_philo(t_box *box, int idx, sem_t *sems[3])
{
	t_philo	philo;

	philo.idx = idx + 1;
	philo.last_meal = box->simul_start;
	philo.box = box;
	philo.sems[FORK] = sems[FORK];
	philo.sems[DEATH] = sems[DEATH];
	philo.sems[PRINT] = sems[PRINT];
	box->philos[idx] = philo;
	philo.pid = fork();
	if (philo.pid < 0)
		exit_with_err("fork() has failed");
	else if (!philo.pid)
	{
		pthread_create(&(philo.tid), NULL, monitor, &philo);
		pthread_detach(philo.tid);
		while (1)
			do_routine(&philo);
	}
}

void	call_philos(t_box *box, sem_t *sems[3])
{
	int	idx;

	idx = 0;
	box->simul_start = get_time();
	while (idx < box->num_of_philo)
		call_philo(box, idx++, sems);
}
