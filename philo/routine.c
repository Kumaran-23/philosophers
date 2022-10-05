/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:10:26 by snair             #+#    #+#             */
/*   Updated: 2022/10/05 14:31:39 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*called when only one philo is present, allowing 
only one fork to be taken and setting status to dead
killing the philo once time_to_die is reached*/
static int	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->fork_right]);
	print_log(*philo, "has taken a fork", GREEN);
	time_spent(philo->time_die);
	return (0);
}

/*locks fork mutex to make sure forks are not stolen*/
static int	take_fork(t_philo *philo)
{
	if (philo->philo_num == 1)
		return (one_philo(philo));
	pthread_mutex_lock(&philo->fork[philo->fork_left]);
	//print_fork(*philo, "has taken left fork", FORK_1);
	print_log(*philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->fork[philo->fork_right]);
	//print_fork(*philo, "has taken right fork", FORK_2);
	print_log(*philo, "has taken a fork", GREEN);
	return (0);
}

/*calls take_fork and takes record of the time a 
philo last ate to check for death as well as decreases 
times_to_eat if argument is present and eats for time_to_eat amount of time.
Once done eating, philo goes to sleep for time_to_sleep amount of time*/
static int	eat_routine(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(philo->eat_time);
	philo->last_ate = current_time_ms();
	pthread_mutex_unlock(philo->eat_time);
	print_log(*philo, "is eating", YELLOW);
	pthread_mutex_lock(philo->eat_amount);
	philo->eat_num--;
	pthread_mutex_unlock(philo->eat_amount);
	time_spent(philo->time_eat);
	if (philo->philo_num != 1)
	{
		pthread_mutex_unlock(&philo->fork[philo->fork_left]);
		pthread_mutex_unlock(&philo->fork[philo->fork_right]);
	}
	if (philo->philo_num == 1)
		pthread_mutex_unlock(&philo->fork[philo->fork_right]);
	return (0);
}

void	sleep_routine(t_philo *philo)
{
	print_log(*philo, "is sleeping", PURPLE);
	time_spent(philo->time_sleep);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		print_log(*philo, "is thinking", RED);
		time_spent(1);
		if (eat_routine(philo))
			break ;
		sleep_routine(philo);
		if (!philo->eat_num)
			return (NULL);
		pthread_mutex_lock(philo->death_mutex);
		if (philo->life_status == DEAD)
		{
			pthread_mutex_unlock(philo->death_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->death_mutex);
	}
	return (NULL);
}