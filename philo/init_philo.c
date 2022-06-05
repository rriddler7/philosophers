/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:41:06 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 17:41:14 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->mutex_forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t)
			* (info->philo_nmb + 1));
	if (!info->mutex_forks)
		return (0);
	while (i <= info->philo_nmb)
	{
		info->mutex_forks[i] = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
		if (!info->mutex_forks[i])
			return (0);
		if (pthread_mutex_init(info->mutex_forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_nmb);
	info->philo_thread = (pthread_t *)malloc(sizeof(pthread_t)
			* info->philo_nmb);
	if (!info->philo || !info->philo_thread)
		return (0);
	while (i < info->philo_nmb)
	{
		info->philo[i].philo_ind = i + 1;
		info->philo[i].fork1 = info->mutex_forks[i];
		info->philo[i].fork2 = info->mutex_forks[(i + 1) % info->philo_nmb];
		info->philo[i].mutex_print = info->mutex_forks[info->philo_nmb];
		info->philo[i].info = info;
		info->philo[i].eat_begin = time_ms();
		info->philo[i].philo_eat_nmb = info->eat_nmb;
		i++;
	}
	return (1);
}

int	init_param(t_info *info, char **argv)
{
	info->philo_nmb = philo_atoi(argv[1]);
	info->time_die = philo_atoi(argv[2]);
	info->time_eat = philo_atoi(argv[3]);
	info->time_sleep = philo_atoi(argv[4]);
	if (argv[5])
		info->eat_nmb = philo_atoi(argv[5]);
	else
		info->eat_nmb = -1;
	info->death = 0;
	info->eat_end = 0;
	if (!init_mutex(info) || !init_philo(info))
		return (0);
	return (1);
}
