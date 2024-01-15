/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_prog_.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 10:57:02 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 16:32:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_close(t_philos *eaters, int i)
{
	admin_ruben(eaters);
	join_thread(eaters, i);
}

void	join_thread(t_philos *eaters, int i)
{
	while (i >= 0)
	{
		pthread_join(eaters[i].thread, NULL);
		i--;
	}
	free(eaters->data->fork);
	multy_mutex_fail(eaters, TIME, eaters->data->nb_philos);
}
