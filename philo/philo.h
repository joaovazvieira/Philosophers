/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:49:58 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 16:35:04 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef enum	e_msg
{
	EAT,
	DIE,
	FORK,
	SLEEP,
	THINK,
}				t_msg;

typedef struct	t_info
{
	int				nb_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				xt_eat;
	int				num_of_created_eaters; // keep in check philos created
	bool			dead;
	long			start_time;
	pthread_mutex_t	god_mutex;
	pthread_mutex_t	god_time_mutex;
	pthread_mutex_t	*fork;
}				t_info;

typedef struct	t_philos
{
	int				id;
	int				meals_ate;
	int				last_ate_time;
	t_info			*data;
	pthread_t		thread;
	pthread_mutex_t	*forkLeft;
	pthread_mutex_t	*forkRight;
}				t_philos;


int				parse(char **argv, t_info *data);
int				create_id_thread(t_info *data, t_philos	*eater, pthread_mutex_t *fork);
int				passed_time(t_info *data);
bool			check_dead_eater(t_info *data);
bool			printer(t_philos *eater, t_msg msg);
long			get_current_time(void);
void			get_fork(pthread_mutex_t *fork, t_philos *eater);
void			admin_ruben(t_philos *eaters);
void			ft_usleep(long time_to_wait, t_philos *eater);
#endif