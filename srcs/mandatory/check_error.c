/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:45:13 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 10:31:13 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	print_err(char *err_msg)
{
	int	i;

	i = 0;
	while (err_msg[i])
		i++;
	write(STDERR_FILENO, err_msg, i);
	write(STDERR_FILENO, "\n", 1);
}

int	check_err(t_box *box, t_err ret)
{
	char	*err_msg;
	
	if (ret == ERR_ARG)
		err_msg = "Error in argument";
	else if (ret == ERR_MALLOC)
		err_msg = "Failed to call malloc()";
	else if (ret == ERR_MUTEX)
		err_msg = "Failed to call pthread_mutex_init()";
	else if (ret == ERR_THD_CREAT)
		err_msg = "Failed to call pthread_create()";
	else
		err_msg = NULL;
	if (err_msg)
	{
		print_err(err_msg);
		return (1);
	}
	return (0);
}
