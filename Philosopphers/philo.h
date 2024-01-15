/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:49:58 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 16:33:16 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MSGFORK "has taken a fork"
# define MSGEAT "is eating"
# define MSGSLEEP "is sleeping"
# define MSGTHINK "is thinking"
# define MSGDIE "died"
# define MSGALLFED "All philos fed"

typedef enum e_error
{
	GOD,
	PRINT,
	START,
	FORKS,
	MEAL,
	TIME,
}			t_error;

typedef enum e_msg
{
	EAT,
	DIE,
	FORK,
	SLEEP,
	THINK,
	ALLFED,
}			t_msg;

typedef struct t_info
{
	int				nb_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				xt_eat;
	int				num_of_created_eaters;
	bool			dead;
	long			start_time;
	pthread_mutex_t	god_mutex;
	pthread_mutex_t	god_start_mutex;
	pthread_mutex_t	god_print_mutex;
	pthread_mutex_t	*fork;
}				t_info;

typedef struct t_philos
{
	int				id;
	int				xt_eat;
	int				last_ate_time;
	bool			meal_check;
	bool			all_eat_print;
	t_info			*data;
	pthread_t		thread;
	pthread_mutex_t	*forkleft;
	pthread_mutex_t	*forkright;
	pthread_mutex_t	god_meal_mutex;
	pthread_mutex_t	god_time_mutex;
}				t_philos;

// program start functions
int				parse(char **argv, t_info *data);
int				var_init(t_info *data, t_philos **eaters);

// thread creation with  static simulation and actions
int				create_id_thread(t_info *data, t_philos	*eater, \
				pthread_mutex_t *fork);
void			join_thread(t_philos *eaters, int i);

// time related functions
int				passed_time(t_info *data);
void			time_assign(t_philos *eater);
void			ft_usleep(unsigned long time_to_wait, t_philos *eater);
unsigned long	get_current_time(void);

// admin, function that oversees the philos behavior
void			admin_ruben(t_philos *eaters);
bool			check_dead_eater(t_info *data);

// mutex functions and clossing prog
void			mutex_init(t_philos *eaters, t_info *data);
void			get_fork(pthread_mutex_t *fork, t_philos *eater);
void			mutex_fail(t_philos *eaters, t_error place);
void			multy_mutex_fail(t_philos *eaters, t_error place, int i);
void			error_close(t_philos *eaters, int i);

// extra functions
bool			printer(t_philos *eater, char *msg, t_msg fed_check);

#endif
