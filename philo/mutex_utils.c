/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 15:53:10 by jovieira      #+#    #+#                 */
/*   Updated: 2023/11/24 19:08:33 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_fail(t_philos *eaters, t_error place)
{
	if (place == GOD)
		pthread_mutex_destroy(&eaters->data->god_mutex);
	else if (place == PRINT)
	{
		pthread_mutex_destroy(&eaters->data->god_print_mutex);
		pthread_mutex_destroy(&eaters->data->god_mutex);
	}
	else if (place == START)
	{
		pthread_mutex_destroy(&eaters->data->god_start_mutex);
		pthread_mutex_destroy(&eaters->data->god_print_mutex);
		pthread_mutex_destroy(&eaters->data->god_mutex);
	}
	free(eaters);
}

static void	mut_fork(t_philos *eaters, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&eaters->data->fork[i]);
		i--;
	}
	mutex_fail(eaters, START);
}

static void	mut_meal(t_philos *eaters, int i, int t)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&eaters[i].god_meal_mutex);
		i--;
	}
	multy_mutex_fail(eaters, FORKS, t);
}

static void	mut_time(t_philos *eaters, int i, int t)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&eaters[i].god_time_mutex);
		i--;
	}
	multy_mutex_fail(eaters, MEAL, t);
}

void	multy_mutex_fail(t_philos *eaters, t_error place, int i)
{
	int	t;

	if (place == FORKS)
		mut_fork(eaters, i);
	else if (place == MEAL)
	{
		t = i;
		mut_meal(eaters, i, t);
		t = 0;
	}
	else
	{
		t = i;
		mut_time(eaters, i, t);
		t = 0;
	}
}
