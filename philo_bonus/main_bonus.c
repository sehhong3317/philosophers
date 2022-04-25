/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 14:04:09 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_box	box;
	t_sems	sems;
	int		i;

	set_table(&box, argc, argv);
	init_semaphores(&box, &sems);
	call_philos(&box, &sems);
	sem_wait(sems.sem_death);
	if (box.min_meal > 0)
		kill(box.pid_for_full, SIGINT);
	i = 0;
	while (i < box.num_of_philo)
		kill(box.philos[i++]->pid, SIGINT);
	finish_meal(&box, &sems);
	return (0);
}
