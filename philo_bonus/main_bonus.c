/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 18:50:12 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_with_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(STDERR_FILENO, str, i);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_box	box;
	t_sems	sems;
	int		i;

	set_table(&box, argc, argv);
	init_semaphores(&box, &sems);
	run_simulation(&box, &sems);
	sem_wait(sems.sem_death);
	if (box.min_meal > 0)
		kill(box.pid_for_full, SIGINT);
	i = 0;
	while (i < box.num_of_philo)
		kill(box.philos[i++]->pid, SIGINT);
	destroy_sems(&sems);
	free_philos(&box);
	return (0);
}
