/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:49:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/27 15:07:39 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NOT_READY	-2
# define ALL_ALIVE	-1
# define PHILO_DEAD	1

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef enum s_err
{
	NO_ERR = 0,
	ERR_ARG,
	ERR_MALLOC,	
	ERR_MUTEX,
	ERR_THD_CREAT
}	t_err;

typedef struct s_philo
{
	pthread_t		tid;
	int				idx;
	time_t			last_meal;
	int				meal_cnt;
	struct s_box	*box;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philo;

typedef struct s_box
{
	int					num_of_philo;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					min_meal;
	time_t				simul_start;
	int					alert;
	int					meal_done;
	pthread_mutex_t		msg_lock;
	pthread_mutex_t		wait_lock;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		*forks;
	t_philo				**philos;
}				t_box;

/* check_err */
int		check_err(t_err ret);

/* do_routine */
int		check_stat(t_box *box);
void	*do_routine(void *arg);

/* fill_up_box */
t_err	fill_up_box(int argc, char **argv, t_box *box);

/* monitor_philos */
void	monitor_philos(t_box *box);

/* rm_table */
void	destroy_mutexes(t_box *box);
void	free_philos(t_box *box, int idx);
t_err	rm_table(t_box *box, int idx, t_err ret);

/* run_simulation */
t_err	run_simulation(t_box *box);

/* set_table */
t_err	set_table(t_box *box);

/* utils */
void	*ft_calloc(size_t count, size_t size);
time_t	get_time(void);
void	set_time(time_t time);
int		print_stat(t_philo *philo, char *stat);
int		eat(t_philo *philo);

#endif