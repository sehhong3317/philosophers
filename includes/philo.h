/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:49:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 17:38:35 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef enum	s_err
{
	NO_ERR = 0,
	ERR_ARG,
	ERR_MALLOC,	
	ERR_MUTEX
}	t_err;

typedef struct s_philo
{
	pthread_t		tid;
	int				idx;
	pthread_mutex_t	fork;
	time_t			last_meal;
	int				meal_cnt;
	struct s_box	*box;
}				t_philo;

typedef struct s_box
{
	int					num_of_philo;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					min_meal;
	time_t				simul_start;
	int					dead_philo;
	int					death_msg;
	int					meal_done;
	pthread_mutex_t		msg_lock;
	t_philo				**philos;
	int					(*fptr)(int, struct s_box *, int);
	int					(*fptr2)(time_t, t_philo *, int, int);
}				t_box;

// check_error
int		check_error(int errno, t_box *box, int mode);

// parse_arguments
void	print_error(char *error_msg);
t_err	set_table(int argc, char **argv, t_box *box);

// mutex_utils
int		initiate_mutex(t_box *box);
int		destroy_mutex(t_box *box);
void	unlock_mutexes(int mode, t_box *box, int th_num);

// print_msg
void	print_philo_death(t_box *box);
void	print_action(int mode, t_box *box, int th_num);

// routine_of_philosophers
int		let_even_philos_run_behind(t_philo *philo, int idx);
int		takes_forks(t_box *box, int th_num, int (*fptr)(int, t_box *, int));
int		eats(t_philo *philo, int th_num, int (*fptr)(int, t_box *, int), \
	int (*fptr2)(time_t, t_philo *, int, int));
int		sleeps(t_philo *philo, int th_num, int (*fptr)(int, t_box *, int), \
	int (*fptr2)(time_t, t_philo *, int, int));

// start_routine
int		check_vitality(int mode, t_box *box, int th_num);
int		check_vitality_w_option(int mode, t_box *box, int th_num);
void	*start_routine(void *arg);

// thread_utils
int		initiate_philo_box(t_box *box);
int		create_philosophers(t_box *box);
int		start_dining(t_box *box);
int		wait_philos(t_box *box);

// time_utils
time_t	get_time(void);
time_t	get_meal_time(t_philo *philo);
int		interval_usleep(time_t interval, t_philo *philo, int mode, int th_num);
int		interval_usleep_w_option(time_t interval, t_philo *philo, int mode, \
	int th_num);

// updage_philo_status
int		update_philo_status_wo_option(t_box *box);
int		update_philo_status_w_option(t_box *box);
void	update_philo_status(t_box *box);

/* utils */
void	*ft_calloc(size_t count, size_t size);

// main
int		finish_simulation(t_box *box);

#endif