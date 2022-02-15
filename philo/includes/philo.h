/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:50:37 by csantos-          #+#    #+#             */
/*   Updated: 2022/02/14 03:21:36 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define DIE 6
# define MAX_INT 2147483647

typedef struct s_param
{
	int				philo_nbr;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				meals_nbr;
	long int		start_time;
	int				is_dead;
	pthread_mutex_t	*death;
	pthread_mutex_t	*text;
	pthread_mutex_t	*who;
}		t_param;

typedef struct s_philo
{
	int				name;
	long int		last_meal;
	int				meals;
	bool			satisfied;
	int				times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mutex_meals;
	pthread_t		philo_thread;
	t_param			*params;
}		t_philo;

/*********
** ACTIONS
**********/

void				meals(t_philo *philo);
int					dinner_finish(t_philo *philo);
void				print_action(t_philo *philo, int action);
void				print_death(t_philo *philo);

/*********
** DINNER
**********/

void				one_philo(t_philo *one);
int					who_died(t_philo *philo);
void				*end_dinner(void *phi);

/*********
** PARSING
**********/

void				init_struct(t_param *param, t_philo *philo);
void				get_params(char **argv, t_param *param,
						pthread_mutex_t **forks);
int					validate_args(int argc);
int					check_entry_args(int argc, char **argv);

/*********
** ROUTINE
**********/

int					eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);
int					routine(t_philo *philo);

/*********
** TIME
**********/

long int			time_calculator(long int start_time);
long int			time_converter(void);
int					time_of_death(long int death_time, long int last_meal);

/*********
** UTILS
**********/

int					ft_isspace(char str);
int					ft_atoi(const char *str);
long long			ft_atol(const char *str);
int					ft_isdigit(int c);

#endif