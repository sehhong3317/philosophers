/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:15:56 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/29 13:59:29 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define FORK_NAME "/sem_fork"
# define PRINT_NAME "/sem_print"
# define MEAL_NAME "/sem_meal"
# define DEATH_NAME "/sem_death"
# define HOLD_NAME	"/sem_hold"

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				idx;
	pid_t			pid;
	pthread_t		tid;
	time_t			last_meal;
	int				meal_cnt;
	struct s_box	*box;
}	t_philo;

typedef struct s_box
{
	int		num_of_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	simul_start;
	int		min_meal;
	t_philo	*philos;
	pid_t	pid_for_full;
	sem_t	*sem_fork;
	sem_t	*sem_print;
	sem_t	*sem_death;
	sem_t	*sem_meal;
	sem_t	*sem_hold;
}	t_box;

t_box	*set_table(int argc, char **argv);
void	call_philos(t_box *box);

/* rm_table */
void	delete_sems(t_box *box);
void	free_philos(t_box *box);
void	kill_philos(t_box *box);

/* exit */
void	print_err(char *str);
void	exit_with_err(char *str);
void	exit_after_free(char *str, t_box *box);
void	exit_after_kill(t_box *box);

/* util */
time_t	get_time(void);
void	philo_eat(t_philo *philo);
void	print_stat(t_philo *philo, char *str);
void	set_time(time_t time);
void	*ft_calloc(size_t count, size_t size);

#endif