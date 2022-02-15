/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:48:21 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 03:23:49 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	one_philo(t_philo *one)
{
	printf("\033[0;33m%ld %i has taken a fork\n\033[0m",
		time_calculator(one->params->start_time), one->name);
	usleep(one->params->time2die * 1000);
	printf("\033[0;31m%ld %i died\n\033[0m",
		time_calculator(one->params->start_time), one->name);
}

int	who_died(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(philo->params->who);
	dead = philo->params->is_dead;
	pthread_mutex_unlock(philo->params->who);
	return (dead);
}

static int	death_time(t_philo *philo)
{
	int		to_die;
	long	l_meal;

	pthread_mutex_lock(philo->mutex_meals);
	to_die = philo->params->time2die;
	l_meal = philo->last_meal;
	pthread_mutex_unlock(philo->mutex_meals);
	if (time_of_death(to_die, l_meal) == 0)
		return (0);
	return (1);
}

static int	verify(t_philo *philo)
{
	int	i;

	i = -1;
	if (who_died(philo) != 0)
		return (1);
	if (death_time(philo) == 0 && philo->satisfied == false)
	{
		pthread_mutex_lock(philo->params->death);
		if (who_died(philo) == 0 && philo->params->philo_nbr != 1)
			print_death(philo);
		pthread_mutex_unlock(philo->params->death);
		return (1);
	}
	if (philo->params->meals_nbr != 0)
	{
		while (++i < philo->params->philo_nbr)
		{
			if (philo[i].meals != philo->params->meals_nbr)
				return (0);
		}
		return (1);
	}
	return (0);
}

void	*end_dinner(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (!verify(philo))
		continue ;
	return (NULL);
}
