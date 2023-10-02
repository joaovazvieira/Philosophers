/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:30:23 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 21:05:41 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Function that feeds the 'eaters' and counts their meals.
*/
static void	eat(t_philos *eater)
{
		get_fork(eater->forkLeft, eater);
		get_fork(eater->forkRight, eater);
		printer(eater, EAT);
		eater->meals_ate++;
		ft_usleep(eater->data->t_eat * 1000, eater);
		pthread_mutex_unlock(eater->forkRight);
		pthread_mutex_unlock(eater->forkLeft);
}

static void	ft_sleep(t_philos *eater)
{

	printer(eater, SLEEP);
	ft_usleep(eater->data->t_sleep *1000, eater);

}

static void	think(t_philos *eater)
{
	printer(eater, THINK);
	// print thinking,crear condição para parar de pensar
}

/*
	* Function creator, routine from pthread_creator.
	* While(1) keeps the loop running until the conditions are made.
*/

static void	*creator(void *temp)
{
	t_philos *eater;
	int	i;

	i = 1;
	eater = (t_philos *)temp;
	eater->last_ate_time = get_current_time();
	while (1) //needs to be constant loop, eat need to verify if already ate
	{
		think(eater);
		eat(eater);
		ft_sleep(eater);
		i++;
	}
	return (0);
}

int	create_id_thread(t_info *data, t_philos	*eater, pthread_mutex_t *fork)
{
	int			i;

	i = 0;
	while (i < eater->data->nb_philos)
	{
		eater[i].id = i + 1;
		eater[i].forkLeft = &fork[i];
		eater[i].forkRight = &fork[(i + 1) % data->nb_philos];
		if (pthread_create(&eater[i].thread, NULL, creator, &eater[i]))
			return (i);
		i++;
	}
	return (i - 1);
}
