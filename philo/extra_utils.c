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

long	get_current_time(void)
{
	struct timeval	stime;

	gettimeofday(&stime, NULL);
	return ((stime.tv_sec * 1000) + (stime.tv_usec / 1000));
}

int	passed_time(t_info *data)
{
	long	current_time;

	current_time = get_current_time();
	return (current_time - data->start_time);
}

static long	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return (t.tv_usec + t.tv_sec * 1000000);
}

// still need to be tweeked, clunky
void	ft_usleep(long time, t_philos *eater)
{
	long	t;

	t = get_time();
	while (time >= get_time() - t)
	{
		usleep(300);
		if (check_dead_eater(eater->data) == true)
			return ;
	}
}

/*
	* Function fork mutex with msg.
*/

void	get_fork(pthread_mutex_t *fork, t_philos *eater) //change func to bool return if dead or alive
{
	if (pthread_mutex_lock(fork) < 0)
		printf("LOCK FAILED\n");
	printer(eater, FORK);
}
