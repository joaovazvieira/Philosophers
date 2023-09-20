/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovieira <jovieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:25:49 by jovieira          #+#    #+#             */
/*   Updated: 2023/09/20 21:19:53 by jovieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ');
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	sum;

	sum = 0;
	i = 0;
	sign = 1;
	while (isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
			sum = (sum * 10) + (str[i] - '0');
			i++;
	}
	if (ft_isdigit(str[i]) == 0 && str[i] != '\0')
		return (-1);
	return (sign * sum);
}

/*
	* Parser function using atoi to convert the input in int,
	* also checking if the input is valid.
*/

int	parse(char **argv, t_info *data)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->xt_eat = ft_atoi(argv[5]);
	else
		data->xt_eat = 0;
	if (data->nb_philos <= 0 || data->t_die <= 0 || data->t_eat <= 0 \
		|| data->t_sleep <= 0 || data->xt_eat == -1)
		return (-1);
	return (0);
}
