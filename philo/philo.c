/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:10:03 by snair             #+#    #+#             */
/*   Updated: 2022/10/09 13:58:33 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*creates a thread for each philosopher as well as a thread to check for death*/
void	threads_create(t_global *table)
{
	int			i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				philo_life, &table->philo[i]))
			error("philo thread create");
		time_spent(1);
		i++;
	}
	if (pthread_create(&table->check, NULL, check_routine, table))
		error("check routine thread create");
}

int	main(int argc, char **argv)
{
	t_global	table;
	int			i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (!init_table(&table, argv))
		{
			threads_create(&table);
			while (i < table.philo_num)
			{
				if (pthread_join(table.philo[i].thread, NULL))
					return (1);
				i++;
			}
			if (pthread_join(table.check, NULL))
				return (1);
			free_all(&table);
		}
	}
	else
		print_error(2);
	return (0);
}