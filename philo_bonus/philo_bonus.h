/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:09:19 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 19:09:25 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <errno.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_info
{
	int			philo_nmb;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			eat_nmb;
	int			philo_ind;
	int			death;
	long		start;
	long		eat_begin;
	pthread_t	philo_death;
	pid_t		*pid;
	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_finish;
}				t_info;

int		philo_atoi(const char *str);
int		verify_arg(int argc, char **argv);
long	time_ms(void);
void	ft_usleep(int time);
int		init_info(t_info *info, char **argv);
int		init_semaphor(t_info *info);
void	philo_print(t_info *info, const char *msg);
int		simulate(t_info *info);

#endif
