/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:13:58 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 20:50:02 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	get_sem_info(t_stype type, char **name, int *value, t_box *box)
{
	if (type == FORK)
	{
		*name = SEM_FORK_NAME;
		*value = box->num_of_philo;
	}
	else if (type == PRINT)
	{
		*name = SEM_PRINT_NAME;
		*value = 1;
	}
	else if (type == MEAL)
	{
		*name = SEM_MEAL_NAME;
		*value = 0;
	}
	else if (type == DEATH)
	{
		*name = SEM_DEATH_NAME;
		*value = 0;
	}
	else if (type == WAIT)
	{
		*name = SEM_WAIT_NAME;
		*value = 1;
	}
	else if (type == EAT)
	{
		*name = SEM_EAT_NAME;
		*value = 1;
	}
}

static	sem_t	*ft_sem_open(t_box *box, t_sems *sems, t_stype type)
{
	char	*sem_name;
	int		init_value;
	sem_t	*ret;

	get_sem_info(type, &sem_name, &init_value, box);
	sem_unlink(sem_name);
	ret = sem_open(sem_name, O_CREAT, 0600, init_value);
	if (ret == SEM_FAILED)
		exit_after_free("Failed to call sem_open()", box, sems);
	return (ret);
}

void	init_semaphores(t_box *box, t_sems *sems)
{
	sems->sem_fork = ft_sem_open(box, sems, FORK);
	sems->sem_print = ft_sem_open(box, sems, PRINT);
	sems->sem_meal = ft_sem_open(box, sems, MEAL);
	sems->sem_death = ft_sem_open(box, sems, DEATH);
	sems->sem_wait = ft_sem_open(box, sems, WAIT);
	sems->sem_eat = ft_sem_open(box, sems, EAT);
}

// void	init_sems(t_box *box, t_sems *sems)
// {
// 	sem_t	*ret;
// 	memset(sems, 0, sizeof(t_sems));
// 	sem_unlink(SEM_FORK_NAME);
// 	ret = sem_open(SEM_FORK_NAME, O_CREAT, 0600, box->num_of_philo);
// 	if (ret == SEM_FAILED)
// 		exit_after_free("Failed to call sem_open()", box, sems);
// 	sem_unlink(SEM_PRINT_NAME);
// 	ret = sem_open(SEM_PRINT_NAME, O_CREAT, 0600, 1);
// 	if (ret == SEM_FAILED)
// 		exit_after_free("Failed to call sem_open()", box, sems);
// 	sem_unlink(SEM_MEAL_NAME);
// 	ret = sem_open(SEM_MEAL_NAME, O_CREAT, 0600, 0);
// 	if (ret == SEM_FAILED)
// 		exit_after_free("Failed to call sem_open()", box, sems);
// 	sem_unlink(SEM_DEATH_NAME);
// 	ret = sem_open(SEM_DEATH_NAME, O_CREAT, 0600, 0);
// 	if (ret == SEM_FAILED)
// 		exit_after_free("Failed to call sem_open()", box, sems);
// 	sem_unlink(SEM_WAIT_NAME);
// 	ret = sem_open(SEM_WAIT_NAME, O_CREAT, 0600, box->num_of_philo);
// 	if (ret == SEM_FAILED)
// 		exit_after_free("Failed to call sem_open()", box, sems);
// }