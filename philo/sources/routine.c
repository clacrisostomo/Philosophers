/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:40:15 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 02:47:29 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	if (dinner_finish(philo) != 0)
		return (1);
	print_action(philo, FORK);
	print_action(philo, FORK);
	if (dinner_finish(philo) != 0)
		return (1);
	print_action(philo, EAT);
	meals(philo);
	if (dinner_finish(philo) != 0)
		return (1);
	usleep(philo->params->time2eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->params->time2sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_action(philo, THINK);
	return (0);
}

int	routine(t_philo *philo)
{
	if (eating(philo) == 1 || philo->satisfied == true)
		return (1);
	if (sleeping(philo) == 1 || philo->satisfied == true)
		return (1);
	if (thinking(philo) == 1 || philo->satisfied == true)
		return (1);
	return (0);
}
