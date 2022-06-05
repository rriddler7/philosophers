/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriddler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:08:03 by rriddler          #+#    #+#             */
/*   Updated: 2022/02/13 19:08:08 by rriddler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_atoi(const char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + ((int)*str - '0');
		if (num > 2147483647)
			return (0);
		str++;
	}
	if (*str && (*str < '0' || *str > '9'))
		return (0);
	return (num);
}

int	verify_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Error: number of arguments is not correct\n");
		return (0);
	}
	while (i < argc)
	{
		if (philo_atoi(argv[i]) < 0)
		{
			printf("Error: argv[i] is negative number\n");
			return (0);
		}
		if (!philo_atoi(argv[i]))
		{
			printf("Error: argv[i] is not correct\n");
			return (0);
		}
		i++;
	}
	return (1);
}

long	time_ms(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == 0)
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	return (0);
}

void	ft_usleep(int time)
{
	long	s_time;

	s_time = time_ms();
	while (time_ms() - s_time < time)
		usleep(500);
}

void	philo_print(t_info *info, const char *msg)
{
	sem_wait(info->sem_print);
	printf("%ld %d %s\n", (time_ms() - info->start),
		info->philo_ind, msg);
	sem_post(info->sem_print);
}
