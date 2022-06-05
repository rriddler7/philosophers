/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:08:37 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 19:08:40 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_sleep(t_info *info)
{
	philo_print(info, "is sleeping");
	ft_usleep(info->time_sleep);
	philo_print(info, "is thinking");
}

void	philo_eat(t_info *info)
{
	sem_wait(info->sem_forks);
	sem_wait(info->sem_forks);
	sem_wait(info->sem_print);
	printf("%ld %d has taken a fork\n",
		time_ms() - info->start, info->philo_ind);
	printf("%ld %d has taken a fork\n",
		time_ms() - info->start, info->philo_ind);
	printf("%ld %d is eating\n",
		time_ms() - info->start, info->philo_ind);
	sem_post(info->sem_print);
	info->eat_begin = time_ms();
	ft_usleep(info->time_eat);
	if (info->eat_nmb > 0)
		info->eat_nmb--;
	sem_post(info->sem_forks);
	sem_post(info->sem_forks);
}

void	*verify_death(void *argv)
{
	t_info	*info;

	info = (t_info *)argv;
	if (info->philo_ind == 0)
	{
		sem_wait(info->sem_finish);
		info->death = 1;
		return (NULL);
	}
	while (info->death == 0)
	{
		if (info->eat_nmb == 0)
			exit(0);
		usleep(500);
		if ((time_ms() - info->eat_begin) >= info->time_die)
		{
			sem_wait(info->sem_print);
			info->death = 1;
			printf("%ld %d is died\n",
				(time_ms() - info->start), info->philo_ind);
			sem_post(info->sem_finish);
			exit(0);
		}
	}
	return (NULL);
}

void	*child_cycle(void *argv)
{
	t_info		*info;
	int			i;

	info = (t_info *)argv;
	pthread_create(&info->philo_death, NULL, verify_death, argv);
	pthread_detach(info->philo_death);
	i = 0;
	while (!info->death && info->eat_nmb != 0)
	{
		if (i == 0 && (!(info->philo_ind % 2)
				|| (info->philo_ind == 1 && (info->philo_nmb % 2))))
			i++;
		else
			philo_eat(info);
		philo_sleep(info);
	}
	return (NULL);
}

int	simulate(t_info *info)
{
	int		i;

	i = 0;
	info->start = time_ms();
	info->eat_begin = time_ms();
	while (i < info->philo_nmb)
	{
		info->pid[i] = fork();
		if (info->pid[i] == 0)
		{
			info->philo_ind = i + 1;
			child_cycle(info);
			return (1);
		}
		if (info->pid[i] < 0)
			return (0);
		i++;
	}
	pthread_create(&info->philo_death, NULL, verify_death, info);
	pthread_detach(info->philo_death);
	return (1);
}
