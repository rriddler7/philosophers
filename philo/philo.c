/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:42:00 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 17:42:03 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulate(t_info *info)
{
	int		i;

	i = 0;
	info->start = time_ms();
	while (i < info->philo_nmb)
	{
		pthread_create(&info->philo_thread[i], NULL,
			start_routin, &info->philo[i]);
		i++;
	}
	i = 0;
	while (i < info->philo_nmb)
	{
		pthread_detach(info->philo_thread[i]);
		i++;
	}
	check_death(info);
}

void	ft_free(t_info *info)
{
	int	i;

	i = 0;
	while (i <= info->philo_nmb)
	{
		if (info->mutex_forks[i])
			free(info->mutex_forks[i]);
		i++;
	}
	if (info->mutex_forks)
		free(info->mutex_forks);
	if (info->philo)
		free(info->philo);
	if (info->philo_thread)
		free(info->philo_thread);
	if (info)
		free(info);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (!verify_arg(argc, argv))
		return (1);
	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (0);
	if (!init_param(info, argv))
	{
		free(info);
		return (1);
	}
	simulate(info);
	ft_free(info);
	return (0);
}
