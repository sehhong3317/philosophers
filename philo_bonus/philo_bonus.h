/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:15:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 08:19:13 by sehhong          ###   ########.fr       */
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

typedef enum s_stype
{
	FORK = 0,
	PRINT,
	MEAL,
	DEATH
}	t_stype;

typedef struct s_sems
{
	sem_t	*sem_fork;
	sem_t	*sem_print;
	sem_t	*sem_death;
	sem_t	*sem_meal;
}	t_sems;

typedef struct s_philo
{
	int				idx;
	pid_t			pid;
	pthread_t		tid;
	time_t			last_meal;
	int				meal_cnt;
	struct s_box	*box;
	t_sems			*sems;
}	t_philo;

typedef struct s_box
{
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	simul_start;
	int		min_meal;
	t_philo	**philos;
	pid_t	pid_for_full;
}	t_box;

void	call_philos(t_box *box, t_sems *sems);
void	init_semaphores(t_box *box, t_sems *sems);
void	set_table(t_box *box, int argc, char **argv);

/* exit */
void	finish_meal(t_box *box, t_sems *sems);
void	exit_with_err(char *str);
void	exit_after_free(char *str, t_box *box, t_sems *sems);
void	kill_philos(t_box *box);
void	exit_after_kill(t_box *box, t_sems *sems);

/* utils */
time_t	get_time(void);
void	print_eat(t_philo *philo);
void	print_stat(t_philo *philo, char *str);
void	set_time(time_t time);
void	*ft_calloc(size_t count, size_t size);

#endif