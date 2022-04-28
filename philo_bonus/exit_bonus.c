/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 01:37:18 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 02:18:21 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(STDERR_FILENO, str, i);
	write(STDERR_FILENO, "\n", 1);
}

void	exit_with_err(char *str)
{
	print_err(str);
	exit(EXIT_FAILURE);
}

void	exit_after_free(char *str, t_box *box)
{
	delete_sems(box);
	free_philos(box);
	exit_with_err(str);
}

void	exit_after_kill(t_box *box)
{
	kill_philos(box);
	delete_sems(box);
	free_philos(box);
	exit_with_err("Failed to create thread");
}
