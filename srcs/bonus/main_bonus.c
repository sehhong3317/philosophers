/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 17:07:17 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_box	box;
	sem_t	*sems[3];
	int		i;

	set_table(&box, argc, argv);
	initiate_semaphores(box, sems);
	call_philos(&box, sems);
	i = 0;
	sem_wait(sems[DEATH]);
	while (i < box.num_of_philo)
		kill(box.philos[i++].pid, SIGINT);
	finish_meal(box, sems);
}
