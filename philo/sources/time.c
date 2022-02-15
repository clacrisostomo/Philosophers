/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:56:58 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 02:18:23 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	time_converter(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long int	time_calculator(long int start_time)
{
	long int	action_time;

	action_time = time_converter();
	return (action_time - start_time);
}

int	time_of_death(long int death_time, long int last_meal)
{
	long int	action_time;

	action_time = time_converter();
	if (last_meal != 0)
		if (action_time - last_meal >= death_time)
			return (0);
	return (1);
}
