/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_philos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:30:55 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 02:29:20 by sehhong          ###   ########.fr       */
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
		usleep(100);
	}
	sem_wait(philo->box->sem_print);
	printf("%ld %d %s\n", get_time() - philo->box->simul_start, \
		philo->idx + 1, "\033[1;31mdied\033[0m");
	sem_post(philo->box->sem_death);
	sem_wait(philo->box->sem_print);
	return (NULL);
}

// TODO usleep(10000); usleep(100); pthread_create처리 ; wait/post처리
static	void	do_routine(t_philo *philo)
{
	t_box	*box;

	box = philo->box;
	// philo->last_meal = philo->box->simul_start;
	philo->last_meal = get_time();
	if (pthread_create(&(philo->tid), NULL, monitor, philo))
	{
		print_err("Failed to create thread");
		sem_post(philo->box->sem_death);
	}
	pthread_create(&(philo->tid), NULL, monitor, philo);
	sem_wait(box->sem_hold);
	sem_post(box->sem_hold);
	if ((philo->idx + 1) % 2 == 0)
		usleep(10000);
		// set_time(philo->box->time_to_eat / 3);
	while (1)
	{
		sem_wait(box->sem_fork);
		print_stat(philo, "\033[33mhas taken a fork\033[0m");
		sem_wait(box->sem_fork);
		print_stat(philo, "\033[33mhas taken a fork\033[0m");
		philo_eat(philo);
		sem_post(box->sem_fork);
		sem_post(box->sem_fork);
		if (philo->box->min_meal > 0 && philo->meal_cnt == philo->box->min_meal)
			sem_post(philo->box->sem_meal);
		print_stat(philo, "\033[35mis sleeping\033[0m");
		set_time(philo->box->time_to_sleep);
		print_stat(philo, "\033[34mis thinking\033[0m");
		// usleep(100);
	}	
}

void	call_philos(t_box *box)
{
	int	idx;

	idx = 0;
	box->simul_start = get_time();
	sem_wait(box->sem_hold);
	while (idx < box->num_of_philo)
	{
		box->philos[idx].pid = fork();
		if (box->philos[idx].pid < 0)
			exit_after_kill(box);
		else if (!box->philos[idx].pid)
			do_routine(&(box->philos[idx]));
		idx++;
	}
	// idx = -1;
	// while (++idx < box->num_of_philo)
		sem_post(box->sem_hold);
}
