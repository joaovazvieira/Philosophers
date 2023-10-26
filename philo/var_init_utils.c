/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_init_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 18:27:04 by jovieira      #+#    #+#                 */
/*   Updated: 2023/10/26 17:20:41 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_fail(t_philos *eaters, t_error place)
{
	if (place == GOD)
		pthread_mutex_destroy(&eaters->data->god_mutex);
	else if (place == PRINT)
	{
		pthread_mutex_destroy(&eaters->data->god_print_mutex);
		pthread_mutex_destroy(&eaters->data->god_mutex);
	}
	free(eaters);
}

static void	multy_mutex_fail(t_philos *eaters, t_error place, int i)
{
	int	t;
	
	if (place == FORKS)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&eaters->data->fork[i]);
			i--;
		}
		mutex_fail(eaters, PRINT);
	}
	else if (place == MEAL)
	{
		t = i;
		while (i >= 0)
		{
			pthread_mutex_destroy(&eaters[i].god_meal_mutex);
			i--;
		}
		multy_mutex_fail(eaters, FORKS, t);
		t = 0;
	}
	else
	{
		t = i;
		while (i >= 0)
		{
			pthread_mutex_destroy(&eaters[i].god_time_mutex);
			i--;
		}
		multy_mutex_fail(eaters, MEAL, t);
		t = 0;
	}
}

void	mutex_init(t_philos *eaters, t_info *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (pthread_mutex_init(&data->god_mutex, NULL) != 0)
		mutex_fail(eaters, GOD);
	if (pthread_mutex_init(&data->god_print_mutex, NULL) !=0 )
		mutex_fail(eaters, PRINT);
	while (i < data->nb_philos)
	{
		eaters[i].xt_eat = data->xt_eat;
		eaters[i].data = data;
		eaters[i].meal_check = false;
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			multy_mutex_fail(eaters, FORKS, i);
		if (pthread_mutex_init(&eaters[i].god_meal_mutex, NULL) != 0)
			multy_mutex_fail(eaters, MEAL, i);
		if (pthread_mutex_init(&eaters[i].god_time_mutex, NULL) != 0)
			multy_mutex_fail(eaters, TIME, i);
		i++;
	}
}

int	var_init(t_info *data, t_philos **eaters)
{
	(*eaters) = malloc(sizeof(t_philos) * data->nb_philos);
	mutex_init(*eaters, data);
	// pthread_mutex_init(&data->god_mutex, NULL);
	data->dead = false;
	data->num_of_created_eaters = 0;
	data->start_time = get_current_time();
	return (0);
}
