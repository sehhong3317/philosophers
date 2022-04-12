/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/13 01:02:35 by sehhong          ###   ########.fr       */
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

void	call_philo(t_box *box, int idx, time_t start_time)
{
	t_philo	philo;

	//philo구조체 기본값 할당
	philo.philo_num = idx + 1;
	philo.last_meal = start_time;
	philo.box = box;
	box->philos[idx] = philo;
	philo.child_pid = fork();
	if (philo.child_pid < 0)
		exit_with_err("fork() has failed");
	else if (!philo.child_pid)
	{
		pthread_create(&(box->philos[idx].tid), NULL, monitor, &philo);
		pthread_detach(box->philos[idx].tid);
		// 모든 프로세스가 동시에 시작하게끔!
		while (get_time_in_ms() < box->simul_start)
			;
		if (idx % 2 == 1)
			set_time(box->time_to_eat / 3);
		while (1)
		{
			eats(box, idx);
			sleeps(box, idx);
			thinks(box, idx);
		}
	}
}

void	finish_meal(t_box box)
{
	sem_close(box.sem_fork);
	sem_close(box.sem_death);
	sem_close(box.sem_print);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink(SEM_DEATH_NAME);
	sem_unlink(SEM_PRINT_NAME);
	free(box.philos);
	box.philos = NULL;
}

int	main(int argc, char **argv)
{
	t_box	box;
	int		idx;
	time_t	start_time;

	set_table(&box, argc, argv);
	idx = 0;
	start_time = get_time_in_ms() + 100;
	box.simul_start = start_time;
	while (idx < box.num_of_philo)
		call_philo(&box, idx++, start_time);
	while (waitpid(-1, NULL, 0) != -1)
		;
	printf("자식 회수 완료");
	// 마지막 식사시간 모두 동일하게 넣어주기
	// idx = 0;
	// sem_wait(box.sem_death);
	// while (idx < box.num_of_philo)
	// 	kill(box.philos[idx++].child_pid, SIGTERM);
	// finish_meal(box);
}