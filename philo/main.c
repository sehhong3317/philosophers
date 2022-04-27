/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:42 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 14:27:06 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_box	box;
	t_err	ret_err;

	ret_err = fill_up_box(argc, argv, &box);
	if (check_err(ret_err) == -1)
		return (EXIT_FAILURE);
	ret_err = set_table(&box);
	if (check_err(ret_err) == -1)
		return (EXIT_FAILURE);
	ret_err = run_simulation(&box);
	if (check_err(ret_err) == -1)
		return (EXIT_FAILURE);
	monitor_philos(&box);
	return (EXIT_SUCCESS);
}
