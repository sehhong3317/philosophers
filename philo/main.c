/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:42 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/24 19:11:49 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_box	box;
	t_err	ret_err;

	ret_err = set_table(argc, argv, &box);
	if (check_err(ret_err) == -1)
		return (EXIT_FAILURE);
	ret_err = call_philos(&box);
	if (check_err(ret_err) == -1)
		return (EXIT_FAILURE);
	run_simulation(&box);
	destroy_mutexes(&box);
	free_philos(&box, box.num_of_philo);
	return (EXIT_SUCCESS);
}
