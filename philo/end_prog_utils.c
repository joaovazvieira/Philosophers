/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_prog_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 16:05:56 by jovieira      #+#    #+#                 */
/*   Updated: 2023/11/24 19:07:54 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
