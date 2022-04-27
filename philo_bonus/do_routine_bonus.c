/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:38:37 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 21:22:03 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((get_time() - philo->last_meal) >= philo->box->time_to_die)
			break ;
	}
	sem_wait(philo->sems->sem_print);
	printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
		philo->idx + 1, "\033[1;31mdied\033[0m");
	sem_post(philo->sems->sem_death);
	return (NULL);
}

void	do_routine(t_philo *philo)
{
	// philo->last_meal = philo->box->simul_start;
	philo->last_meal = get_time();
	// if (pthread_create(&(philo->tid), NULL, monitor, philo))
		// exit_after_kill(philo->box, philo->sems);
	pthread_create(&(philo->tid), NULL, monitor, philo);
	sem_wait(philo->sems->sem_wait);
	sem_post(philo->sems->sem_wait);
	if ((philo->idx + 1) % 2 == 0)
		set_time(philo->box->time_to_eat / 3);
	while (1)
	{
		sem_wait(philo->sems->sem_fork);
		print_stat(philo, "\033[33mhas taken a fork\033[0m");
		sem_wait(philo->sems->sem_fork);
		print_stat(philo, "\033[33mhas taken a fork\033[0m");
		philo_eat(philo);
		sem_post(philo->sems->sem_fork);
		sem_post(philo->sems->sem_fork);
		print_stat(philo, "\033[35mis sleeping\033[0m");
		set_time(philo->box->time_to_sleep);
		print_stat(philo, "\033[34mis thinking\033[0m");
	}	
}
