/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:15:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/19 15:38:43 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define SEM_FORK_NAME "/sem_fork"
# define SEM_PRINT_NAME "/sem_print"
# define SEM_MEAL_NAME "/sem_meal"
# define SEM_DEATH_NAME "/sem_death"

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef struct	s_sems
{
	sem_t	*sem_fork;
	sem_t	*sem_print;
	sem_t	*sem_death;
	sem_t	*sem_meal;
}	t_sems;

typedef struct	s_philo
{
	int				idx;
	pid_t			pid;
	pthread_t		tid;
	time_t			last_meal;
	int				meal_cnt;
	struct s_box	*box;
	t_sems			*sems;
}	t_philo;

typedef struct	s_box
{
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	simul_start;
	int		min_meal;
	t_philo	**philos;
}	t_box;

void	call_philos(t_box *box, t_sems *sems);
void	finish_meal(t_box *box, t_sems *sems);
void	initiate_semaphores(t_box *box, t_sems *sems);
void	set_table(t_box *box, int argc, char **argv);

/* utils */
void	exit_with_err(char *str);
time_t	get_time(void);
void	print_stat(t_philo *philo, char *str, int if_eats);
void	set_time(time_t time);
void	*ft_calloc(size_t count, size_t size);

#endif