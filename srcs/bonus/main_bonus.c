/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 16:06:14 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	call_philos(t_box *box, sem_t *sems[3])
{
	int	idx;

	idx = 0;
	box->simul_start = get_time();
	while (idx < box->num_of_philo)
		call_philo(box, idx++, sems);
	if (box->min_meal > 0)
		check_if_full(box);
}


int	main(int argc, char **argv)
{
	t_box	box;
	sem_t	*sems[4];
	int		i;

	set_table(&box, argc, argv);	//여기서 malloc
	initiate_semaphores(&box, sems);
	call_philos(&box, sems);
	printf("메인: sem : %p\n", (int *)sems[DEATH]);
	sem_wait(sems[DEATH]);
	i = 0;
	while (i < box.num_of_philo)
	{
		printf("다음 pid를 없앤다: %d\n", box.philos[i].pid);
		kill(box.philos[i++].pid, SIGINT);
	}
	finish_meal(&box, sems);
}
