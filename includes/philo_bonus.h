/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:15:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/17 11:15:07 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define SEM_FORK_NAME	"/sem_fork"
# define SEM_DEATH_NAME	"/sem_death"
# define SEM_PRINT_NAME	"/sem_print"

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef enum e_sem
{
	FORK = 0,
	DEATH,
	PRINT
}	t_sem;

typedef struct	s_philo
{
	int				idx;
	pid_t			pid;
	pthread_t		tid;
	time_t			last_meal;
	struct	s_box	*box;
	sem_t			*sems[3];
}	t_philo;

typedef struct	s_box
{
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	simul_start;
	int		min_meal;
	t_philo	*philos;
}	t_box;

void	call_philos(t_box *box, sem_t **sems);
void	exit_with_err(char *str);
void	parse_args(int argc, char **argv, t_box *box);
void	do_routine(t_philo philo);
void	set_table(t_box *box, int argc, char **argv);
time_t	get_time(void);
void	set_time(time_t time);

#endif