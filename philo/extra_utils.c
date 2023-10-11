/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:49:16 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 21:12:55 by jovieira         ###   ########.fr       */
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

// static long	get_time(void)
// {
// 	struct timeval	t;

// 	if (gettimeofday(&t, NULL) == -1)
// 		return (0);
// 	// printf("time function get_time = %li\n", t.tv_usec + t.tv_sec * 1000000);
// 	return (t.tv_usec + t.tv_sec * 1000000);
// }

// still need to be tweeked, clunky
void	ft_usleep(unsigned long time_to_wait, t_philos *eater)
{
	// unsigned long	start_time;

	(void)eater;
	time_to_wait = time_to_wait + get_current_time();
	while (get_current_time() < time_to_wait)
		usleep(100);
}

/*
	* Function fork mutex with msg.
*/

void	get_fork(pthread_mutex_t *fork, t_philos *eater) //change func to bool return if dead or alive
{
	pthread_mutex_lock(fork);
	printer(eater, FORK);
}
