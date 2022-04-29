/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:33:58 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 17:05:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_meal_checker(t_box *box)
{
	int	i;

	box->pid_for_full = fork();
	if (box->pid_for_full < 0)
		exit_after_free("Failed to call fork()", box);
	else if (!box->pid_for_full)
	{
		i = -1;
		usleep(1500);
		while (++i < box->num_of_philo)
			sem_wait(box->sem_meal);
		sem_post(box->sem_death);
		sem_wait(box->sem_print);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	t_box	*box;

	if (argc != 5 && argc != 6)
		exit_with_err("Invalid number of argument");
	box = set_table(argc, argv);
	if (box->min_meal > 0)
		create_meal_checker(box);
	call_philos(box);
	sem_wait(box->sem_death);
	kill_philos(box);
	delete_sems(box);
	free_philos(box);
	return (0);
}
