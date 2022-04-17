/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 14:08:06 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// while (get_time_in_ms() < philo->box->simul_start)
	// 	;
	// while ((get_time_in_ms() - philo->last_meal) < philo->box->time_to_die)
	// 	;
	// sem_wait(philo->box->sem_print);
	// printf("%ldms %d is died\n", \
	// 	get_time_in_ms() - philo->box->simul_start, philo->philo_num);
	// sem_post(philo->box->sem_print);
	// sem_post(philo->box->sem_death);
	return (NULL);
}

void	finish_meal(t_box box, sem_t *sem_fork, sem_t *sem_death, \
	sem_t *sem_print)
{
	sem_close(sem_fork);
	sem_close(sem_death);
	sem_close(sem_print);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DEATH_NAME);
	sem_unlink(SEM_PRINT_NAME);
	free(box.philos);
	box.philos = NULL;
}

static	void	initiate_semaphores(t_box box, sem_t **sem_fork, \
	sem_t **sem_death, sem_t **sem_print)
{
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DEATH_NAME);
	sem_unlink(SEM_PRINT_NAME);
	*sem_fork = sem_open(SEM_FORK_NAME, O_CREAT, 0600, box.num_of_philo);
	*sem_death = sem_open(SEM_DEATH_NAME, O_CREAT, 0600, 0);
	*sem_print = sem_open(SEM_PRINT_NAME, O_CREAT, 0600, 1);
	if (*sem_fork == SEM_FAILED || *sem_death == SEM_FAILED ||
		*sem_print == SEM_FAILED)
	{
		finish_meal(box, *sem_fork, *sem_death, *sem_print);
		exit_with_err("failed to open semaphore");	
	}
}

int	main(int argc, char **argv)
{
	t_box	box;
	sem_t	*sem_fork;
	sem_t	*sem_death;
	sem_t	*sem_print;

	set_table(&box, argc, argv);
	initiate_semaphores(box, sem_fork, sem_death, sem_print);
	call_philos(&box, sem_fork, sem_death, sem_print);
	while (waitpid(-1, NULL, 0) != -1)
		;
	printf("자식 회수 완료");
	// idx = 0;
	// sem_wait(box.sem_death);
	// while (idx < box.num_of_philo)
	// 	kill(box.philos[idx++].child_pid, SIGTERM);
	finish_meal(box, sems);
}