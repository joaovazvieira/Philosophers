/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:14:36 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 19:37:08 by jovieira         ###   ########.fr       */
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

	// pthread_mutex_lock(&data->god_mutex);
	dead = data->dead;
	// pthread_mutex_unlock(&data->god_mutex);
	return (dead);
}

static bool	admin_helper(t_philos *eater)
{
	int	t;
// need to add mutex for safety
	t = get_current_time();
	if (t - eater->last_ate_time > eater->data->t_die)
	{
		printer(eater, DIE);
		eater->data->dead = true;
		return (true);
	}
	return (false);
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

	if	(eaters->data->num_of_created_eaters != eaters->data->nb_philos)
		return ;
	while (1)
	{
		i = 0;
		while (i < eaters->data->nb_philos)
		{
			if (admin_helper(&eaters[i]) == true)
				return ;
			i++;
		}
	}
}
