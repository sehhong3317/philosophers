/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 08:40:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 22:12:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	prepare_philo(t_box *box, int idx, t_sems *sems)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
	{
		if (box->min_meal > 0)
			kill(box->pid_for_full, SIGINT);
		exit_after_free("Failed to call malloc()", box, sems);
	}
	philo->idx = idx;
	philo->box = box;
	philo->sems = sems;
	box->philos[idx] = philo;
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
	int		idx;
	t_philo	*philo;

	idx = 0;
	box->simul_start = get_time();
	sem_wait(sems->sem_wait);
	while (idx < box->num_of_philo)
	{
		philo = box->philos[idx];
		philo->pid = fork();
		if (philo->pid < 0)
			exit_after_kill(box, sems);
		else if (!philo->pid)
			do_routine(philo);
		idx++;
	}
	sem_post(sems->sem_wait);
}

void	run_simulation(t_box *box, t_sems *sems)
{
	int		idx;

	idx = 0;
	while (idx < box->num_of_philo)
		prepare_philo(box, idx++, sems);
	if (box->min_meal > 0)
		create_meal_checker(box, sems);
	// box->simul_start = get_time();
	call_philos(box, sems);
}
