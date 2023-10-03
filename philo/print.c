/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:51:28 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 20:56:28 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Function use to print different msg using the dead checker function,
	* using enum.
*/

bool	printer(t_philos *eater, t_msg msg)
{
	int	time;

	pthread_mutex_lock(&eater->data->god_mutex);
	time = passed_time(eater->data);
	if (check_dead_eater(eater->data) == true)
		return (true);
	if (msg == DIE)
		printf("%5i %i died\n", time, eater->id);
	else if (msg == EAT)
	{
		//eater->last_ate_time = time;
		printf("%5i %i eating\n", time, eater->id);
	}
	else if (msg == FORK)
		printf("%5i %i took a fork\n", time, eater->id);
	else if (msg == SLEEP)
		printf("%5i %i sleeping\n", time, eater->id);
	else
		printf("%5i %i thinking\n", time, eater->id);
	pthread_mutex_unlock(&eater->data->god_mutex);
	return (false);
}
