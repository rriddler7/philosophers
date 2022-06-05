/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:08:22 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 19:08:26 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphor(t_info *info)
{
	sem_unlink("/sem_forks");
	info->sem_forks = sem_open("/sem_forks", O_CREAT, S_IRWXU, info->philo_nmb);
	if (info->sem_forks == SEM_FAILED)
		return (0);
	sem_unlink("/sem_print");
	info->sem_print = sem_open("/sem_print", O_CREAT, S_IRWXU, 1);
	if (info->sem_print == SEM_FAILED)
		return (0);
	sem_unlink("/sem_finish");
	info->sem_finish = sem_open("/sem_finish", O_CREAT, S_IRWXU, 0);
	if (info->sem_finish == SEM_FAILED)
		return (0);
	return (1);
}

int	init_info(t_info *info, char **argv)
{
	info->pid = NULL;
	info->philo_nmb = philo_atoi(argv[1]);
	info->time_die = philo_atoi(argv[2]);
	info->time_eat = philo_atoi(argv[3]);
	info->time_sleep = philo_atoi(argv[4]);
	if (argv[5])
		info->eat_nmb = philo_atoi(argv[5]);
	else
		info->eat_nmb = -1;
	info->death = 0;
	info->philo_ind = 0;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * info->philo_nmb);
	if (!info->pid)
		return (0);
	if (!init_semaphor(info))
		return (0);
	return (1);
}
