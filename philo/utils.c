/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:09:52 by snair             #+#    #+#             */
/*   Updated: 2022/10/04 12:09:53 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message)
{
	printf("Error %s\n", message);
	return (-1);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

/*to print log with timestamp and message in change of state 
if message is not "died"*/
void	print_log(t_philo philo, char *message, char *colour)
{
	unsigned long int	time;

	time = current_time_ms() - philo.start_time;
	if (philo.life_status == ALIVE || !ft_strncmp(message, "died", 4))
	{
		pthread_mutex_lock(philo.msg);
		printf("%5lu  %sPhilo %5d %s%s\n", time, colour, philo.id, message, EC);
		pthread_mutex_unlock(philo.msg);
	}
}

/*for testing the number of the forks taken*/
void	print_fork(t_philo philo, char *str, t_status status)
{
	long unsigned int	time;

	time = current_time_ms() - philo.start_time;
	if (philo.life_status == ALIVE)
	{
		if (status == FORK_1)
		{
			pthread_mutex_lock(philo.msg);
			printf("%5lu  Philosopher %5d %s [%d]\n",
				time, philo.id, str, philo.fork_left);
			pthread_mutex_unlock(philo.msg);
		}
		if (status == FORK_2)
		{
			pthread_mutex_lock(philo.msg);
			printf("%5lu  Philosopher %5d %s [%d]\n",
				time, philo.id, str, philo.fork_right);
			pthread_mutex_unlock(philo.msg);
		}
	}
}
