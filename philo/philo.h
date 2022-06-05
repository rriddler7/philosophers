/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:42:12 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 17:42:15 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_ind;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	pthread_mutex_t	*mutex_print;
	struct s_info	*info;
	long			eat_begin;
	int				philo_eat_nmb;
}				t_philo;

typedef struct s_info
{
	int				philo_nmb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_nmb;
	t_philo			*philo;
	pthread_t		*philo_thread;
	pthread_mutex_t	**mutex_forks;
	long			start;
	int				death;
	int				eat_end;
}				t_info;

int		philo_atoi(const char *str);
int		verify_arg(int argc, char **argv);
long	time_ms(void);
void	ft_usleep(int time);
int		init_param(t_info *info, char **argv);
void	philo_print(t_philo *philo, const char *msg);
void	*start_routin(void *argv);
void	check_death(t_info *info);

#endif
