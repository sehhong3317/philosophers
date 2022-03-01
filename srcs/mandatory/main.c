/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:42 by sehhong           #+#    #+#             */
/*   Updated: 2022/03/01 18:20:03 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_dining_philosophers(t_info *info)
{
	int	errno;

	errno = initiate_philo_info(info);
	if (check_error(errno, info, ERR_MALLOC) == -1)
		return (-1);
	errno = initiate_mutex(info);
	if (check_error(errno, info, ERR_MUTEX_INIT) == -1)
		return (-1);
	errno = create_philosophers(info);
	if (check_error(errno, info, ERR_THR_CREATE) == -1)
		return (-1);
	errno = start_dining(info);
	if (check_error(errno, info, ERR_TIME) == -1)
		return (-1);
	update_philo_status(info);
	return (0);
}

int	finish_simulation(t_info *info)
{
	int	errno;

	errno = wait_philos(info);
	if (check_error(errno, info, ERR_THR_JOIN) == -1)
		return (-1);
	errno = destroy_mutex(info);
	if (check_error(errno, info, ERR_MUTEX_DESTROY) == -1)
		return (-1);
	free(info->philos);
	info->philos = NULL;
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		errno;

	errno = parse_arguments(argc, argv, &info);
	if (check_error(errno, &info, ERR_ARG) == -1)
		return (1);
	errno = start_dining_philosophers(&info);
	if (errno == -1)
		return (1);
	errno = finish_simulation(&info);
	if (errno == -1)
		return (1);
	return (0);
}
