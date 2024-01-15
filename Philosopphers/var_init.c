/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 18:27:04 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 14:29:33 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_assign(t_philos *eater)
{
	int	i;

	i = 0;
	eater->data->start_time = get_current_time();
	while (i < eater->data->nb_philos)
	{
		eater[i].last_ate_time = eater->data->start_time;
		i++;
	}
}

void	mutex_init(t_philos *eaters, t_info *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->god_mutex, NULL) != 0)
		mutex_fail(eaters, GOD);
	if (pthread_mutex_init(&data->god_print_mutex, NULL) != 0)
		mutex_fail(eaters, PRINT);
	if (pthread_mutex_init(&data->god_start_mutex, NULL) != 0)
		mutex_fail(eaters, START);
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
	if (!eaters)
		return (printf("ERROR\nMalloc Fail\n"), 1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->fork)
		return (printf("ERROR\nMalloc Fail\n"), 1);
	mutex_init(*eaters, data);
	data->dead = false;
	data->num_of_created_eaters = 0;
	return (0);
}
