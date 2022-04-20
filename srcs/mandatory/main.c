/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:34:42 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 17:51:22 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_box *box)
{
	int	ret;

	// ret = initiate_philo_box(box);
	// if (check_error(ret, box, ERR_MALLOC) == -1)
	// 	return (-1);
	ret = initiate_mutex(box);
	if (check_error(ret, box, ERR_MUTEX_INIT) == -1)
		return (-1);
	ret = create_philosophers(box);
	if (check_error(ret, box, ERR_THR_CREATE) == -1)
		return (-1);
	ret = start_dining(box);
	if (check_error(ret, box, ERR_TIME) == -1)
		return (-1);
	update_philo_status(box);
	return (0);
}

t_err	call_philo(t_box *box, int idx)
{
	t_philo	*philo;

	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (ERR_MALLOC);
	philo->idx = idx + 1;
	philo->last_meal = box->simul_start;
	philo->meal_cnt = 0;
	philo->box = box;
	if (pthread_mutex_init(&philo->fork, NULL))
		return (ERR_MUTEX);
	return (NO_ERR);
}

t_err	call_philos(t_box *box)
{
	int		idx;
	t_err	ret;

	idx = -1;
	if (pthread_mutex_init(&box->msg_lock, NULL))
	{
		free_philos(box);
		return (ERR_MUTEX);
	}
	box->simul_start = get_time(); //?
	while (++idx < box->num_of_philo)
	{	
		ret = call_philo(box, idx);
		if (ret)
		{	
			free_philos(box);
			// mutex_destroy(); -> msg_lock, fork모두
			return (ret);
		}
	}
}

int	finish_simulation(t_box *box)
{
	int	ret;

	ret = wait_philos(box);
	if (check_error(ret, box, ERR_THR_JOIN) == -1)
		return (-1);
	ret = destroy_mutex(box);
	if (check_error(ret, box, ERR_MUTEX_DESTROY) == -1)
		return (-1);
	free(box->philos);
	box->philos = NULL;
	return (0);
}

int	main(int argc, char **argv)
{
	t_box	box;
	t_err	ret;

	ret = set_table(argc, argv, &box);	//여기서 box->philos malloc
	if (check_err(&box, ret))
		return (EXIT_FAILURE);
	ret = call_philos(&box);	//각 philo malloc + mutex_init
	if (check_err(&box, ret))
		return (EXIT_FAILURE);
	ret = finish_simulation(&box);
	if (ret == -1)
		return (1);
	return (EXIT_SUCCESS);
}
