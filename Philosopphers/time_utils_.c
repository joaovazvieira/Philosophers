/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils_.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 16:49:16 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 15:02:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* get_current_time / passed_time
	* Functions used all around the programme to keep the time in check.
*/
unsigned long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	passed_time(t_info *data)
{
	long	current_time;

	current_time = get_current_time();
	return (current_time - data->start_time);
}

void	ft_usleep(unsigned long time_to_wait, t_philos *eater)
{
	time_to_wait = time_to_wait + get_current_time();
	while (get_current_time() < time_to_wait && !check_dead_eater(eater->data))
		usleep(500);
}

// Function fork mutex with msg.
void	get_fork(pthread_mutex_t *fork, t_philos *eater)
{
	pthread_mutex_lock(fork);
	printer(eater, MSGFORK, FORK);
}
