/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:45:13 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 17:51:24 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_err(char *err_msg)
{
	int	i;

	i = 0;
	while (err_msg[i])
		i++;
	write(STDERR_FILENO, err_msg, i);
	write(STDERR_FILENO, "\n", 1);
}

void	free_philos(t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->num_of_philo)
	{
		if (box->philos[i])
		{
			free(box->philos[i]);
			box->philos[i] = NULL;
		}
	}
	free(box->philos);
	box->philos = NULL;
}

void	

int	check_err(t_box *box, t_err ret)
{
	char	*err_msg;
	
	err_msg = NULL;
	if (ret == ERR_ARG)
		err_msg = "Error in argument";
	else if (ret == ERR_MALLOC)
		err_msg = "Failed to call malloc()";
	else if (ret == ERR_MUTEX)
		err_msg = "Failed to call pthread_mutex_init()";
	if (ret)
	{
		print_err(err_msg);
		return (1);
	}
	return (0);
}

// int	check_error(int ret, t_box *box, int mode)
// {
// 	if (ret == -1)
// 	{
// 		if (mode == ERR_ARG)
// 			print_error("Error in argument.\n");
// 		else if (mode == ERR_MALLOC)
// 			print_error("Malloc() has failed.\n");
// 		else
// 		{
// 			if (mode == ERR_MUTEX_INIT)
// 				print_error("pthread_mutex_init() has failed.\n");
// 			else if (mode == ERR_THR_CREATE)
// 				print_error("pthread_create() has failed.\n");
// 			else if (mode == ERR_THR_JOIN)
// 				print_error("pthread_join() has failed.\n");
// 			else if (mode == ERR_MUTEX_DESTROY)
// 				print_error("pthread_mutex_destroy() has failed.\n");
// 			free(box->philos);
// 			box->philos = NULL;
// 		}
// 		return (-1);
// 	}
// 	return (0);
// }
