/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:12:52 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 04:15:29 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_struct(t_param *param, t_philo *philo)
{
	philo->name = 0;
	philo->meals = 0;
	philo->last_meal = 0;
	philo->satisfied = false;
	philo->times_eaten = 0;
	param->is_dead = 0;
	param->philo_nbr = 0;
	param->time2die = 0;
	param->time2eat = 0;
	param->time2sleep = 0;
	param->meals_nbr = 0;
	param->start_time = 0;
}

void	get_params(char **argv, t_param *param, pthread_mutex_t **forks)
{
	*forks = NULL;
	param->philo_nbr = ft_atoi(argv[1]);
	param->time2die = ft_atoi(argv[2]);
	param->time2eat = ft_atoi(argv[3]);
	param->time2sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->meals_nbr = ft_atoi(argv[5]);
	else
		param->meals_nbr = 0;
	param->death = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	param->text = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	param->who = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(param->death, NULL);
	pthread_mutex_init(param->text, NULL);
	pthread_mutex_init(param->who, NULL);
}

int	validate_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments.\n");
		return (1);
	}
	return (0);
}

static int	check_entry_args_b(char **argv, int i)
{
	long int	temp;

	temp = 0;
	if (!ft_isdigit(*argv[i]))
	{
		printf("Error: arguments must be all digits.\n");
		return (1);
	}
	else if (ft_atoi(argv[i]) == 0)
	{
		printf("Error: invalid argument, use non zero arguments.\n");
		return (1);
	}
	temp = ft_atoi(argv[i]);
	if (!temp)
	{
		printf("Error: arguments must be integers.\n");
		return (1);
	}
	return (0);
}

int	check_entry_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atol(argv[i]) > MAX_INT)
		{
			printf("Error: argument bigger than maximum integer.\n");
			return (1);
		}
		else if (argv[i][0] == 45)
		{
			printf("Error: invalid argument, use positive numbers.\n");
			return (1);
		}
		else if (check_entry_args_b(argv, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
