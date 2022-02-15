/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 03:11:07 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 03:21:09 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*dinner(void *arg)
{
	t_philo	*philo_n;

	philo_n = (t_philo *)arg;
	pthread_mutex_lock(philo_n->mutex_meals);
	philo_n->last_meal = philo_n->params->start_time;
	pthread_mutex_unlock(philo_n->mutex_meals);
	if (philo_n->params->philo_nbr == 1)
	{
		one_philo(philo_n);
		return (NULL);
	}
	if (philo_n->name % 2 == 0)
		usleep(1000);
	while (!routine(philo_n))
		continue ;
	return (NULL);
}

static void	init_philosophers(t_philo *philo, t_param *param,
			pthread_mutex_t **forks, int total_philo)
{
	pthread_t	waiter;
	int			i;

	i = -1;
	while (++i < total_philo)
	{
		philo[i].name = i + 1;
		philo[i].right_fork = &(*forks)[i];
		philo[i].left_fork = &(*forks)[i + 1];
		philo[i].mutex_meals = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t) * 1);
		pthread_mutex_init(philo[i].mutex_meals, NULL);
		philo[i].params = param;
	}
	philo[i - 1].left_fork = &(*forks)[0];
	i = -1;
	param->start_time = time_converter();
	while (++i < total_philo)
		pthread_create(&philo[i].philo_thread, NULL, &dinner,
			(void *)&philo[i]);
	pthread_create(&waiter, NULL, &end_dinner, philo);
	i = -1;
	while (++i < total_philo)
		pthread_join(philo[i].philo_thread, NULL);
	pthread_join(waiter, NULL);
}

static void	init_forks(pthread_mutex_t **forks, int total_philo)
{
	int	i;

	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_philo);
	i = -1;
	while (++i < total_philo)
		pthread_mutex_init(&(*forks)[i], NULL);
}

static void	destroy_free_thread(t_param param, t_philo *philo,
			pthread_mutex_t *forks)
{
	pthread_mutex_destroy(param.text);
	pthread_mutex_destroy(param.who);
	pthread_mutex_destroy(param.death);
	free(param.who);
	free(param.text);
	free(param.death);
	free(forks);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_param			param;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (validate_args(argc) == 1 || (check_entry_args(argc, argv) == 1))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_struct(&param, philo);
	get_params(argv, &param, &forks);
	init_forks(&forks, param.philo_nbr);
	init_philosophers(philo, &param, &forks, param.philo_nbr);
	while (i < param.philo_nbr && forks)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(philo[i].mutex_meals);
		free(philo[i].mutex_meals);
		i++;
	}
	destroy_free_thread(param, philo, forks);
	return (0);
}
