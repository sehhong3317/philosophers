/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:32 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 23:53:58 by sehhong          ###   ########.fr       */
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
	int		i;

	set_table(&box, argc, argv);
	init_semaphores(&box);
	run_simulation(&box);
	sem_wait(box.sem_death);
	if (box.min_meal > 0)
		kill(box.pid_for_full, SIGINT);
	i = 0;
	while (i < box.num_of_philo)
		kill(box.philos[i++]->pid, SIGINT);
	destroy_sems(&box);
	free_philos(&box);
	return (0);
}
