/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 09:49:12 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/25 11:53:50 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int					dead_philo;
	int					meal_done;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	t_philo				**philos;
}				t_box;

/* call_philos */
t_err	call_philos(t_box *box);

/* check_err */
int		check_err(t_err ret);

/* do_routine */
int		check_stat(t_box *box);
void	*do_routine(void *arg);

/* rm_table */
void	detach_philos(t_box *box, int idx);
void	destroy_mutexes(t_box *box);
void	free_philos(t_box *box, int idx);

/* run_simuation */
void	run_simulation(t_box *box);

/* set_table */
t_err	set_table(int argc, char **argv, t_box *box);

/* utils */
void	*ft_calloc(size_t count, size_t size);
time_t	get_time(void);
void	set_time(time_t time);
int		print_stat(t_philo *philo, char *stat);
int		print_eat(t_philo *philo);

#endif