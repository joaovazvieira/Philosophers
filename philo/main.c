/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 14:27:55 by jovieira      #+#    #+#                 */
/*   Updated: 2023/10/26 15:10:03 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Variables initialization function.
*/
// check how many mutex fork were created
// static int	var_init(t_info *data, t_philos **eaters)
// {
// 	int	i;

// 	i = 0;
// 	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
// 	(*eaters) = malloc(sizeof(t_philos) * data->nb_philos);
// 	// mutex_init(*eaters, data);
// 	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
// 	pthread_mutex_init(&data->god_mutex, NULL);
// 	pthread_mutex_init(&data->god_print_mutex, NULL);
// 	while (i < data->nb_philos)
// 	{
// 		(*eaters)[i].xt_eat = data->xt_eat;
// 		(*eaters)[i].data = data;
// 		(*eaters)[i].meal_check = false;
// 		pthread_mutex_init(&data->fork[i], NULL);
// 		pthread_mutex_init(&(*eaters)[i].god_meal_mutex, NULL);
// 		pthread_mutex_init(&(*eaters)[i].god_time_mutex, NULL);
// 		i++;
// 	}
// 	data->dead = false;
// 	data->num_of_created_eaters = 0;
// 	data->start_time = get_current_time();
// 	return (0);
// }

// print on parse the error itself
// free the ammount created, dont free all
int	main(int argc, char **argv)
{
	int			i;
	t_info		data;
	t_philos	*eaters;

	if (argc < 5)
		return (1);
	if (parse(argv, &data) == -1)
		return (1);
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
	free(data.fork);
	free(eaters);
	return (0);
}
