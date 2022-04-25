/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 08:40:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 13:21:11 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	do_routine(t_philo *philo)
{
	sem_wait(philo->sems->sem_fork);
	print_stat(philo, "\033[33mhas taken a fork\033[0m");
	sem_wait(philo->sems->sem_fork);
	print_stat(philo, "\033[33mhas taken a fork\033[0m");
	print_eat(philo);
	set_time(philo->box->time_to_eat);
	sem_post(philo->sems->sem_fork);
	sem_post(philo->sems->sem_fork);
	print_stat(philo, "\033[35mis sleeping\033[0m");
	set_time(philo->box->time_to_sleep);
	print_stat(philo, "\033[34mis thinking\033[0m");
}

static	void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((get_time() - philo->last_meal) < philo->box->time_to_die)
		;
	sem_wait(philo->sems->sem_print);
	printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
		philo->idx, "\033[1;31m died\033[0m");
	sem_post(philo->sems->sem_death);
	return (NULL);
}

static	void	call_philo(t_box *box, int idx, t_sems *sems)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
	{
		if (box->min_meal > 0)
			kill(box->pid_for_full, SIGINT);
		exit_after_free("Failed to call malloc()", box, sems);
	}
	philo->idx = idx + 1;
	philo->last_meal = box->simul_start;
	philo->box = box;
	philo->sems = sems;
	box->philos[idx] = philo;
	box->philos[idx]->pid = fork();
	if (philo->pid < 0)
		exit_after_kill(box, sems);
	else if (!philo->pid)
	{
		if (pthread_create(&(philo->tid), NULL, monitor, philo))
			exit_after_kill(box, sems);
		pthread_detach(philo->tid);
		while (1)
			do_routine(philo);
	}
}

static	void	create_meal_checker(t_box *box, t_sems *sems)
{
	int	i;

	box->pid_for_full = fork();
	if (box->pid_for_full < 0)
		exit_after_free("Failed to call fork()", box, sems);
	else if (!box->pid_for_full)
	{
		i = -1;
		while (++i < box->num_of_philo)
			sem_wait(sems->sem_meal);
		sem_post(sems->sem_death);
		sem_wait(sems->sem_print);
		exit(EXIT_SUCCESS);
	}
}

void	call_philos(t_box *box, t_sems *sems)
{
	int			idx;

	idx = 0;
	if (box->min_meal > 0)
		create_meal_checker(box, sems);
	box->simul_start = get_time();
	while (idx < box->num_of_philo)
		call_philo(box, idx++, sems);
}
