/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:49:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/10 15:15:38 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_ARG 0
# define ERR_MALLOC	1
# define ERR_MUTEX_INIT 2
# define ERR_THR_CREATE 3
# define ERR_TIME 4
# define ERR_THR_JOIN 5
# define ERR_MUTEX_DESTROY 6

# define PHILO_FORK_1 0
# define PHILO_FORK_2 1
# define PHILO_EATING 2
# define PHILO_SLEEPING 3
# define PHILO_THINKING 4
# define PHILO_WAIT	5

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	fork;
	time_t			last_meal;
	int				thread_num;
	int				meal_count;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int					num_of_philo;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					num_of_meal;
	time_t				simul_start;
	int					dead_philo;
	int					death_msg;
	int					meal_done;
	pthread_mutex_t		msg_lock;
	t_philo				*philos;
	int					(*fptr)(int, struct s_info *, int);
	int					(*fptr2)(time_t, t_philo *, int, int);
}				t_info;

// check_error
int		check_error(int errno, t_info *info, int mode);

// parse_arguments
void	print_error(char *error_msg);
int		parse_arguments(int argc, char **argv, t_info *info);

// mutex_utils
int		initiate_mutex(t_info *info);
int		destroy_mutex(t_info *info);
void	unlock_mutexes(int mode, t_info *info, int th_num);

// print_msg
void	print_philo_death(t_info *info);
void	print_action(int mode, t_info *info, int th_num);

// routine_of_philosophers
int		let_even_philos_run_behind(t_philo *philo, int thread_num);
int		takes_forks(t_info *info, int th_num, int (*fptr)(int, t_info *, int));
int		eats(t_philo *philo, int th_num, int (*fptr)(int, t_info *, int), \
	int (*fptr2)(time_t, t_philo *, int, int));
int		sleeps(t_philo *philo, int th_num, int (*fptr)(int, t_info *, int), \
	int (*fptr2)(time_t, t_philo *, int, int));

// start_routine
int		check_vitality(int mode, t_info *info, int th_num);
int		check_vitality_w_option(int mode, t_info *info, int th_num);
void	*start_routine(void *arg);

// thread_utils
int		initiate_philo_info(t_info *info);
int		create_philosophers(t_info *info);
int		start_dining(t_info *info);
int		wait_philos(t_info *info);

// time_utils
time_t	get_time_in_ms(void);
time_t	get_meal_time(t_philo *philo);
int		interval_usleep(time_t interval, t_philo *philo, int mode, int th_num);
int		interval_usleep_w_option(time_t interval, t_philo *philo, int mode, \
	int th_num);

// updage_philo_status
int		update_philo_status_wo_option(t_info *info);
int		update_philo_status_w_option(t_info *info);
void	update_philo_status(t_info *info);

// main
int		start_dining_philosophers(t_info *info);
int		finish_simulation(t_info *info);

#endif