/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:45:14 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 01:55:10 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isspace(char str)
{
	if (str == 0x20 || (str >= 0x09 && str <= 0x0d))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	sign;

	i = 0;
	j = 0;
	sign = -1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = 1;
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 - (*str++ - '0');
		if (j < i)
		{
			if (sign < 0)
				return (-1);
			return (0);
		}
		j = i;
	}
	return (i * sign);
}

long long	ft_atol(const char *str)
{
	int				i;
	int				negative;
	long long int	number;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	negative = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			negative = -1;
	}
	number = 0;
	while (ft_isdigit(str[i]))
		number = (number * 10) + (negative * (str[i++] - '0'));
	return (number);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
