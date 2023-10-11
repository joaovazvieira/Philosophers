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

	pthread_mutex_lock(&eater->data->god_print_mutex);
	time = passed_time(eater->data);
	if (check_dead_eater(eater->data) == true)
	{	
		pthread_mutex_unlock(&eater->data->god_print_mutex);
		return (true);
	}
	if (msg == DIE)
		printf("%i %i died\n", time, eater->id);
	else if (msg == EAT)
		printf("%i %i is eating\n", time, eater->id);
	else if (msg == FORK)
		printf("%i %i has taken a fork\n", time, eater->id);
	else if (msg == SLEEP)
		printf("%i %i is sleeping\n", time, eater->id);
	else
		printf("%i %i is thinking\n", time, eater->id);
	pthread_mutex_unlock(&eater->data->god_print_mutex);
	return (false);
}
