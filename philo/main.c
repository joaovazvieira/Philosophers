/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 14:27:55 by jovieira      #+#    #+#                 */
/*   Updated: 2023/11/22 15:29:52 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (1);
	i = create_id_thread(&data, eaters, data.fork);
	admin_ruben(eaters);
	join_thread(eaters, i);
	return (0);
}
