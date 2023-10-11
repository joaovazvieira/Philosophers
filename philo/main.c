/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:27:55 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 20:58:15 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Variables initialization function.
*/

static int	var_init(t_info *data, t_philos **eaters)
{
	int	i;

	i = 0;
	(*eaters) = malloc(sizeof(t_philos) * data->nb_philos);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	pthread_mutex_init(&data->god_mutex, NULL);
	pthread_mutex_init(&data->god_time_mutex, NULL);
	pthread_mutex_init(&data->god_print_mutex, NULL);
	while (i < data->nb_philos) // check how many mutex fork were created
	{
		(*eaters)[i].data = data;
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	data->dead = false;
	data->num_of_created_eaters = 0;
	data->start_time = get_current_time();
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_info		data;
	t_philos	*eaters;
	
	if (argc < 5)
		return (1);
	if (parse(argv, &data) == -1)
		return (1); // print on parse the error itself
	if (var_init(&data, &eaters) == 1)
	{
		printf("ERROR\nInitializing variables\n");
		return (1);
	}
	i = create_id_thread(&data, eaters, data.fork);
	admin_ruben(eaters);
	while (i >= 0)
	{
		pthread_join(eaters[i].thread, NULL);
		i--;
	}
	free(data.fork); // free the ammount created, dont free all
	free(eaters);
	return (0);
}
