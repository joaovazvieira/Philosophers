/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 14:27:55 by jovieira      #+#    #+#                 */
/*   Updated: 2024/01/15 16:34:15 by jovieira      ########   odam.nl         */
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
	if (i - 1 != data.nb_philos)
	{
		error_close(eaters, i);
		return (1);
	}
	admin_ruben(eaters);
	join_thread(eaters, i);
	return (0);
}
