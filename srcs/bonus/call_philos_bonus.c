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
	sem_wait(philo->sems->sem_fork);
	print_stat(philo, "\033[1;32mhas taken a fork\033[0m", 0);
	sem_wait(philo->sems->sem_fork);
	print_stat(philo, "\033[1;32mhas taken a fork\033[0m", 0);
	print_stat(philo, "\033[32mis eating\033[0m", 1);
	set_time(philo->box->time_to_eat);
	sem_post(philo->sems->sem_fork);
	sem_post(philo->sems->sem_fork);
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
	sem_wait(philo->sems->sem_print);
	printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
		philo->idx, "\033[31mis died\033[0m");
	sem_post(philo->sems->sem_death);
	return (NULL);
}

static	void	call_philo(t_box *box, int idx, t_sems *sems)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit_with_err("failed to call malloc()");
	philo->idx = idx + 1;
	philo->last_meal = box->simul_start;
	philo->meal_cnt = 0;
	philo->box = box;
	philo->sems = sems;
	box->philos[idx] = philo;
	box->philos[idx]->pid = fork();
	if (philo->pid < 0)
		exit_with_err("fork() has failed");
	else if (!philo->pid)
	{
		pthread_create(&(philo->tid), NULL, monitor, philo);
		pthread_detach(philo->tid);
		while (1)
			do_routine(philo);
	}
}

static	void	*monitor_if_all_full(void *arg)
{
	int		i;
	t_box 	*box;

	box = (t_box *)arg;
	i = -1;
	while (++i < box->num_of_philo)
	{
		sem_wait(box->philos[0]->sems->sem_meal);
		printf("somone finished its meal(%d)\n", i);
	}
	sem_wait(box->philos[0]->sems->sem_print);
	sem_post(box->philos[0]->sems->sem_death);
	return (NULL);
}

void	call_philos(t_box *box, t_sems *sems)
{
	int			idx;
	pthread_t	tid;

	idx = 0;
	box->simul_start = get_time();
	while (idx < box->num_of_philo)
		call_philo(box, idx++, sems);
	if (box->min_meal > 0)
	{
		pthread_create(&tid, NULL, monitor_if_all_full, box);
		pthread_detach(tid);
	}
}


