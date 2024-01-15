/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_mach.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 15:51:28 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 15:36:13 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Function use to print different msg using the dead checker function,
	* using enum.
*/

bool	printer(t_philos *eater, char *msg, t_msg fed_check)
{
	int	time;

	pthread_mutex_lock(&eater->data->god_print_mutex);
	time = passed_time(eater->data);
	if (check_dead_eater(eater->data) == true && fed_check != ALLFED)
	{
		pthread_mutex_unlock(&eater->data->god_print_mutex);
		return (true);
	}
	printf("%i %i %s\n", time, eater->id, msg);
	pthread_mutex_unlock(&eater->data->god_print_mutex);
	return (false);
}
