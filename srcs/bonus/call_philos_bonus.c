/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 08:40:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 14:10:59 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static	void	call_philo(t_box *box, int idx, sem_t *sems)
{
	t_philo	philo;

	//philo구조체 기본값 할당
	philo.idx = idx + 1;
	philo.last_meal = box->simul_start;
	philo.box = box;
	philo.sems[FORK] = &sems[FORK];
	philo.sems[DEATH] = &sems[DEATH];
	philo.sems[PRINT] = &sems[PRINT];
	box->philos[idx] = philo;
	philo.pid = fork();
	if (philo.pid < 0)
		exit_with_err("fork() has failed");
	else if (!philo.pid)
	{
		// pthread_create(&(box->philos[idx].tid), NULL, monitor, &philo);
		// pthread_detach(box->philos[idx].tid);
		while (1)
			do_routine(philo);
	}
}

void	call_philos(t_box *box, sem_t *sem_fork, sem_t *sem_death, \
	sem_t *sem_print)
{
	int		idx;

	idx = 0;
	box->simul_start = get_time();
	while (idx < box->num_of_philo)
		call_philo(box, idx++, *sems);
}