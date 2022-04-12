/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/13 00:10:21 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((get_time_in_ms() - philo->last_meal) < philo->box->time_to_die)
		;
	sem_post(philo->box->sem_death);
	return (NULL);
}

void	call_philo(t_box *box, int idx, time_t start_time)
{
	t_philo	philo;

	//philo구조체 기본값 할당
	philo.philo_num = idx + 1;
	philo.last_meal = start_time + 1000;
	philo.box = box;
	box->philos[idx] = philo;
	philo.child_pid = fork();
	if (philo.child_pid < 0)
		exit_with_err("fork() has failed");
	else if (!philo.child_pid)
	{
		//쓰레드 생성
		pthread_create(&(box->philos[idx].tid), NULL, monitor, &philo);
		pthread_detach(box->philos[idx].tid);
		while (get_time_in_ms() < philo.last_meal)
			;
		// 짝수 철학자는 조금 늦게 시작하기
		// 철학자 루틴 돌기(밥먹기, 잠자기, 생각하기)
		while (1)
		{
			take_forks(box, idx);
			eat();
			sleep();
			think();
		}
	}
}

int	main(int argc, char **argv)
{
	t_box	box;
	int		idx;
	time_t	start_time;

	set_table(&box, argc, argv);
	idx = 0;
	start_time = get_time_in_ms();
	while (idx < box.num_of_philo)
		call_philo(&box, idx++, start_time);
	while (waitpid(-1, NULL, 0) != -1)
		;
	printf("I got my all children");
	// 마지막 식사시간(box->philos[idx].last_meal)이 모두 동일하게 넣어주기?
	// 
	// idx = 0;
	// sem_wait(box.sem_death);
	// while (idx < box.num_of_philo)
	// 	kill(box.philos[idx++].child_pid, SIGTERM);
	// sem_close(box.sem_fork);
	// sem_close(box.sem_death);
	// sem_close(box.sem_print);
	// sem_unlink(box.sem_fork);
	// sem_unlink(box.sem_death);
	// sem_unlink(box.sem_print);
	// free(box.philos);
	// box.philos = NULL;
}