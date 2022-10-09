/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_eat_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:10:52 by snair             #+#    #+#             */
/*   Updated: 2022/10/09 15:35:37 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*to end program once number of times to eat reaches 0 or continue if not*/
int	meal_count(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_amount);
	if (!philo->eat_num)
	{
		pthread_mutex_unlock(philo->eat_amount);
		return (0);
	}
	pthread_mutex_unlock(philo->eat_amount);
	return (1);
}

/*to check if a philo has dead by comparing 
(time last ate + time to die) <= current_time_ms, 
philo life status is set to DEAD*/
int	check_death(t_philo *philo)
{
	long	time;
	long	death;

	pthread_mutex_lock(philo->eat_time);
	time = current_time_ms() - philo->last_ate;
	death = philo->time_die;
	pthread_mutex_unlock(philo->eat_time);
	if (time >= death)
	{
		pthread_mutex_lock(philo->death_mutex);
		philo->life_status = DEAD;
		pthread_mutex_unlock(philo->death_mutex);
		return (DEAD);
	}
	return (ALIVE);
}

/*to set all philos life_status to DEAD because if not the philo that dies
states gets printed after death*/
static int	set_death(t_global *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_lock(table->philo[i].death_mutex);
		table->philo[i].life_status = DEAD;
		pthread_mutex_unlock(table->philo[i].death_mutex);
		i++;
	}
	return (0);
}

/*function to pass into creating a thread to monitor death and amount ate*/
void	*check_routine(void *arg)
{
	t_global	*table;
	int			i;

	i = 0;
	table = (t_global *)arg;
	while (1)
	{
		if (table->philo_num == i)
			i = 0;
		if (check_death(&table->philo[i]) == DEAD)
		{
			if (!meal_count(&table->philo[i]))
				return (NULL);
			set_death(table);
			print_log(table->philo[i], "died", CYAN);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}