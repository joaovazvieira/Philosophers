/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotine.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/30 17:30:23 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 15:57:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Function that feeds the 'eaters' and counts their meals.
*/
static void	ft_eat(t_philos *eater)
{
	get_fork(eater->forkright, eater);
	get_fork(eater->forkleft, eater);
	printer(eater, MSGEAT, EAT);
	eater->xt_eat--;
	pthread_mutex_lock(&eater->god_time_mutex);
	eater->last_ate_time = get_current_time();
	pthread_mutex_unlock(&eater->god_time_mutex);
	ft_usleep(eater->data->t_eat, eater);
	pthread_mutex_unlock(eater->forkleft);
	pthread_mutex_unlock(eater->forkright);
}

static void	ft_sleep(t_philos *eater)
{
	printer(eater, MSGSLEEP, SLEEP);
	ft_usleep(eater->data->t_sleep, eater);
}

static bool	ft_think(t_philos *eater)
{
	if (eater->data->t_die - ((int)get_current_time() - eater->last_ate_time) \
		> eater->data->t_eat)
		ft_usleep(200, eater);
	printer(eater, MSGTHINK, THINK);
	return (check_dead_eater(eater->data));
}

/*
	* Function sim, routine from pthread_creator.
	* While(1) keeps the loop running until the conditions are made.
*/
static void	*sim(void *temp)
{
	t_philos	*eater;

	eater = (t_philos *)temp;
	pthread_mutex_lock(&eater->data->god_start_mutex);
	if (eater->data->num_of_created_eaters != eater->data->nb_philos)
		return (NULL);
	pthread_mutex_unlock(&eater->data->god_start_mutex);
	if (eater->id % 2)
		usleep (1100);
	while (1)
	{
		ft_eat(eater);
		ft_sleep(eater);
		if (ft_think(eater) == true)
			break ;
		if (eater->xt_eat == 0)
		{
			pthread_mutex_lock(&eater->god_meal_mutex);
			eater->meal_check = true;
			pthread_mutex_unlock(&eater->god_meal_mutex);
		}
	}
	return (0);
}

// *this eaters is the the last 
int	create_id_thread(t_info *data, t_philos	*eater, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&eater->data->god_start_mutex);
	while (i < eater->data->nb_philos)
	{
		eater[i].id = i + 1;
		eater[i].forkleft = &fork[i];
		eater[i].forkright = &fork[(i + 1) % data->nb_philos];
		if (eater[i].id == eater->data->nb_philos)
		{
			eater[i].forkleft = eater[i].forkright;
			eater[i].forkright = &fork[i];
		}
		if (pthread_create(&eater[i].thread, NULL, sim, &eater[i]) != 0)
			break ;
		data->num_of_created_eaters++;
		i++;
	}
	time_assign(eater);
	pthread_mutex_unlock(&eater->data->god_start_mutex);
	return (i - 1);
}
