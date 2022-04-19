/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 15:30:57 by sehhong          ###   ########.fr       */
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
	printf("나는 부모. 내 첫자식 pid: %d\n", box->philos[0].pid);
	printf("나는 부모. 내 둘째자식 pid: %d\n", box->philos[1].pid);
	printf("나는 부모. 내 셋째자식 pid: %d\n", box->philos[2].pid);
	printf("나는 부모. 내 넷째자식 pid: %d\n", box->philos[3].pid);
}


int	main(int argc, char **argv)
{
	t_box	box;
	sem_t	*sems[3];
	int		i;

	set_table(&box, argc, argv);	//여기서 malloc
	initiate_semaphores(&box, sems);
	call_philos(&box, sems);
	waitpid(-1, NULL, 0);
	printf("나는 부모. 내 첫자식 pid: %d\n", box.philos[0].pid);
	i = 0;
	while (i < box.num_of_philo)
		kill(box.philos[i++].pid, SIGINT);
	finish_meal(&box, sems);
}
