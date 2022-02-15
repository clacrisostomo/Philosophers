/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:19:49 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 03:23:30 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	meals(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_meals);
	philo->last_meal = time_converter();
	philo->meals++;
	if (philo->params->meals_nbr != 0)
	{
		if (philo->meals == philo->params->meals_nbr
			&& philo->satisfied == false)
			philo->satisfied = true;
	}
	pthread_mutex_unlock(philo->mutex_meals);
}

int	dinner_finish(t_philo *philo)
{
	if (who_died(philo) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	print_action(t_philo *philo, int action)
{
	long int	time;

	pthread_mutex_lock(philo->params->text);
	time = time_calculator(philo->params->start_time);
	if (who_died(philo) == 0)
	{
		if (action == FORK)
			printf("\033[0;33m%ld %i has taken a fork\n\033[0m", time,
				philo->name);
		else if (action == EAT)
			printf("\033[0;34m%ld %i is eating\n\033[0m", time, philo->name);
		else if (action == SLEEP)
			printf("\033[0;35m%ld %i is sleeping\n\033[0m", time, philo->name);
		else if (action == THINK)
			printf("\033[0;32m%ld %i is thinking\n\033[0m", time, philo->name);
		else if (action == DIE)
			printf("\033[0;31m%ld %i died\n\033[0m", time, philo->name);
	}
	else if (action == DIE)
		printf("\033[0;31m%ld %i died\n\033[0m", time, philo->name);
	pthread_mutex_unlock(philo->params->text);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->params->who);
	philo->params->is_dead = philo->name;
	pthread_mutex_unlock(philo->params->who);
	print_action(philo, DIE);
}
