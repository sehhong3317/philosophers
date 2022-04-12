/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:45:13 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/10 15:17:16 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_error(char *error_msg)
{
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
}

int	check_error(int errno, t_info *info, int mode)
{
	if (errno == -1)
	{
		if (mode == ERR_ARG)
			print_error("Error in argument.\n");
		else if (mode == ERR_MALLOC)
			print_error("Malloc() has failed.\n");
		else
		{
			if (mode == ERR_MUTEX_INIT)
				print_error("pthread_mutex_init() has failed.\n");
			else if (mode == ERR_THR_CREATE)
				print_error("pthread_create() has failed.\n");
			else if (mode == ERR_THR_JOIN)
				print_error("pthread_join() has failed.\n");
			else if (mode == ERR_MUTEX_DESTROY)
				print_error("pthread_mutex_destroy() has failed.\n");
			free(info->philos);
			info->philos = NULL;
		}
		return (-1);
	}
	return (0);
}
