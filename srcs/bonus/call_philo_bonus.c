/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 08:40:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 15:59:58 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	do_routine(t_philo *philo)
{
	sem_wait(philo->sems[FORK]);
	print_stat(philo, "\033[1;32mhas taken a fork\033[0m", 0);
	sem_wait(philo->sems[FORK]);
	print_stat(philo, "\033[1;32mhas taken a fork\033[0m", 0);
	print_stat(philo, "\033[32mis eating\033[0m", 1);
	set_time(philo->box->time_to_eat);
	sem_post(philo->sems[FORK]);
	sem_post(philo->sems[FORK]);
	print_stat(philo, "\033[1;35mis sleeping\033[0m", 0);
	set_time(philo->box->time_to_sleep);
	print_stat(philo, "\033[1;34mis thinking\033[0m", 0);
}

static	void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((get_time() - philo->last_meal) < philo->box->time_to_die)
		;	
	sem_wait(philo->sems[PRINT]);
	printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
		philo->idx, "\033[31mis died\033[0m");
	sem_post(philo->sems[DEATH]);
	// exit(EXIT_SUCCESS);
	return (NULL);
}

void	call_philo(t_box *box, int idx, sem_t *sems[3])
{
	t_philo	philo;
	int		i;

	philo.idx = idx + 1;
	philo.last_meal = box->simul_start;
	philo.meal_cnt = 0;
	philo.box = box;
	i = -1;
	while (++i <= MEAL)
		philo.sems[i] = sems[i];
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



