/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:09:12 by snair             #+#    #+#             */
/*   Updated: 2022/10/04 12:09:14 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*destory and free all fork mutex and memory allocated*/
static void	free_fork(pthread_mutex_t *fork, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_mutex_destroy(&fork[i]))
			break ;
		i++;
	}
	free(fork);
}

/*destory all mutexes and free memory allocated for philo when initialized*/
void	free_all(t_global *table)
{
	free_fork(table->philo->fork, table->philo_num);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->eat_time);
	pthread_mutex_destroy(&table->eat_amount);
	pthread_mutex_destroy(&table->msg);
	free(table->philo);
}
