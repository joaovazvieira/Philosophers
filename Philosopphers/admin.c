/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   admin.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 18:14:36 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 15:58:05 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Function that allow the admin to set 'eaters' as dead.
	* main mutex used to operate this check function.
*/
bool	check_dead_eater(t_info *data)
{
	bool	dead;

	pthread_mutex_lock(&data->god_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->god_mutex);
	return (dead);
}

static bool	admin_helper(t_philos *eater)
{
	int	t;

	t = get_current_time();
	pthread_mutex_lock(&eater->god_time_mutex);
	if (t - eater->last_ate_time > eater->data->t_die)
	{
		printer(eater, MSGDIE, DIE);
		pthread_mutex_lock(&eater->data->god_mutex);
		eater->data->dead = true;
		pthread_mutex_unlock(&eater->god_time_mutex);
		pthread_mutex_unlock(&eater->data->god_mutex);
		return (true);
	}
	pthread_mutex_unlock(&eater->god_time_mutex);
	return (false);
}

static int	meal_check(t_philos *eaters, int i, int eaters_fed)
{
	pthread_mutex_lock(&eaters[i].god_meal_mutex);
	if (eaters[i].meal_check == true)
		eaters_fed++;
	pthread_mutex_unlock(&eaters[i].god_meal_mutex);
	return (eaters_fed);
}

static int	done_eating(t_philos *eaters, int eaters_fed)
{
	if (eaters_fed == eaters->data->nb_philos)
	{
		pthread_mutex_lock(&eaters->data->god_mutex);
		eaters->data->dead = true;
		pthread_mutex_unlock(&eaters->data->god_mutex);
		printf("All philos fed\n");
		return (1);
	}
	return (0);
}

/*
	* Function admin keeps in check if the number of threads created,
	* match the number of philos requested,
	* With the while(1) runs together with the main thread function,
	* checking if any 'eater' died in conjunction with admin_helper.
*/
void	admin_ruben(t_philos *eaters)
{
	int	i;
	int	eaters_fed;

	if (eaters->data->num_of_created_eaters != eaters->data->nb_philos)
		return ;
	usleep(1500);
	while (1)
	{
		eaters_fed = 0;
		i = 0;
		while (i < eaters->data->nb_philos)
		{
			eaters_fed = meal_check(eaters, i, eaters_fed);
			if (admin_helper(&eaters[i]) == true)
				return ;
			i++;
		}
		if (done_eating(eaters, eaters_fed) == 1)
			break ;
		usleep(1500);
	}
}
