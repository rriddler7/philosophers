/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:08:54 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 19:08:57 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_end(t_info *info)
{
	int	i;

	if (info->eat_nmb > 0)
	{
		i = 0;
		while (i < info->philo_nmb)
		{
			waitpid(-1, NULL, WUNTRACED);
			if (info->death == 1)
				break ;
			i++;
		}
	}
	else
		waitpid(-1, NULL, WUNTRACED);
	i = 0;
	while (i < info->philo_nmb)
	{
		kill(info->pid[i], SIGTERM);
		i++;
	}
}

void	ft_free(t_info *info)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_finish");
	if (info->pid)
		free(info->pid);
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
	if (!init_info(info, argv))
	{
		ft_free(info);
		return (1);
	}
	if (!simulate(info))
		exit(1);
	wait_end(info);
	ft_free(info);
	return (0);
}
