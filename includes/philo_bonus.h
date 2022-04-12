/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:15:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/12 22:50:28 by sehhong          ###   ########.fr       */
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
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef struct	s_philo
{
	int				philo_num;
	pid_t			child_pid;
	pthread_t		tid;
	time_t			last_meal;
	struct	s_box	*box;
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
	sem_t	*sem_fork;
	sem_t	*sem_death;
	sem_t	*sem_print;
}	t_box;

void	parse_arguments(int argc, char **argv, t_box *box);
void	exit_with_err(char *str);
void	set_table(t_box *box, int argc, char **argv);
time_t	get_time_in_ms(void);

#endif