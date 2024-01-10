/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 16:49:16 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/10 18:45:36 by jovieira      ########   odam.nl         */
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
	const int	x = 100 + (5 * eater->data->nb_philos);

	time_to_wait = time_to_wait + get_current_time();
	while (get_current_time() < time_to_wait && !check_dead_eater(eater->data))
		usleep(x);
}

// Function fork mutex with msg.
void	get_fork(pthread_mutex_t *fork, t_philos *eater, t_fork ref)
{
	pthread_mutex_lock(fork);
	if (ref == RIGHT)
		eater->right_fork = true;
	else
		eater->left_fork = true;
	printer(eater, FORK);
}
