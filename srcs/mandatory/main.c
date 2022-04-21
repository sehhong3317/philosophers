/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:42 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/21 16:26:51 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_box	box;
	t_err	ret_err;

	// 여기서 box->philos + box->forks malloc
	ret_err = set_table(argc, argv, &box);
	if (check_err(&box, ret_err))
		return (EXIT_FAILURE);
	// 각 philo안에서 malloc + mutex_init
	ret_err = call_philos(&box);
	if (check_err(&box, ret_err))
		return (EXIT_FAILURE);
	run_simulation(&box);
	rm_table(&box);
	// destroy_mutex(&box, box.num_of_philo);
	// free_philos(&box, box.num_of_philo);
	return (EXIT_SUCCESS);
}
