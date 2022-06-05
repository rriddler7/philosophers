/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:41:38 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 17:41:43 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	if (philo->info->death == 1)
		return ;
	philo_print(philo, "is sleeping");
	ft_usleep(philo->info->time_sleep);
	if (philo->info->death == 1)
		return ;
	philo_print(philo, "is thinking");
}

void	eat_count(t_philo *philo)
{
	philo->eat_begin = time_ms();
	ft_usleep(philo->info->time_eat);
	if (philo->philo_eat_nmb > 0)
		philo->philo_eat_nmb--;
	if (philo->philo_eat_nmb == 0)
		philo->info->eat_end++;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	if (philo->info->death == 1)
	{
		pthread_mutex_unlock(philo->fork1);
		return ;
	}
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork2);
	if (philo->info->death == 1)
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return ;
	}
	pthread_mutex_lock(philo->mutex_print);
	printf("%ld %d has taken a fork\n", time_ms() - philo->info->start,
		philo->philo_ind);
	printf("%ld %d is eating\n", time_ms() - philo->info->start,
		philo->philo_ind);
	pthread_mutex_unlock(philo->mutex_print);
	eat_count(philo);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	*start_routin(void *argv)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)argv;
	while (!philo->info->death && philo->philo_eat_nmb != 0)
	{
		if (i == 0 && (!(philo->philo_ind % 2)
				|| (philo->philo_ind == 1 && (philo->info->philo_nmb % 2))))
			i++;
		else
			philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	check_death(t_info *info)
{
	int		i;

	i = 0;
	while (info->eat_end < info->philo_nmb && info->death == 0)
	{
		if ((time_ms() - info->philo[i].eat_begin) >= info->time_die
			&& info->philo[i].philo_eat_nmb != 0)
		{
			pthread_mutex_lock(info->philo[i].mutex_print);
			printf("%ld %d died\n", (time_ms() - info->start),
				info->philo[i].philo_ind);
			info->death = 1;
			pthread_mutex_unlock(info->philo[i].mutex_print);
			break ;
		}
		i = (i + 1) % info->philo_nmb;
	}
}
