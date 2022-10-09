/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:10:16 by snair             #+#    #+#             */
/*   Updated: 2022/10/09 15:23:01 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*allocate memory and initialize one fork per philo*/
static int	init_forks(t_global *table, t_philo *philo)
{
	int	i;

	i = 0;
	philo->fork = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!philo->fork)
		error("fork mutex memory allocation");
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&philo->fork[i], NULL))
			error("fork mutex init");
		i++;
	}
	return (0);
}

/*to comply with norm*/
static void	fork_order(t_global *table, int i)
{
	table->philo[i].fork_left = i;
	table->philo[i].fork_right = (i + 1) % table->philo_num;
}

/*initialize all other mutex values for philo struct, 
separate function because of norm line number*/
static void	philo_mutex(t_global *table, int i)
{
	table->philo[i].death_mutex = &table->death_mutex;
	table->philo[i].eat_amount = &table->eat_amount;
	table->philo[i].eat_time = &table->eat_time;
	table->philo[i].msg = &table->msg;
}

/*initialize all philo values*/
static int	init_philo(t_global *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * table->philo_num);
	if (!philo)
		error("philo memory allocation");
	init_forks(table, philo);
	while (++i < table->philo_num)
	{
		table->philo[i].id = i + 1;
		table->philo[i].life_status = ALIVE;
		table->philo[i].fork = philo->fork;
		fork_order(table, i);
		table->philo[i].time_sleep = table->time_sleep;
		table->philo->philo_num = table->philo_num;
		table->philo[i].time_die = table->time_die;
		table->philo[i].time_eat = table->time_eat;
		table->philo[i].start_time = table->start_time;
		table->philo[i].eat_num = table->eat_num;
		table->philo[i].last_ate = current_time_ms();
		philo_mutex(table, i);
	}
	free(philo);
	return (0);
}

/*initialize all global values from arguments recieved
amd initialize all global mutex as well as allocate memory
for philo*/
int	init_table(t_global *table, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->start_time = current_time_ms();
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	table->eat_num = -1;
	if (argv[5])
		table->eat_num = ft_atoi(argv[5]);
	if (arg_check(table, argv))
		return (1);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->eat_amount, NULL);
	pthread_mutex_init(&table->eat_time, NULL);
	pthread_mutex_init(&table->msg, NULL);
	table->philo = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->philo)
		error("init table philo memory allocation");
	init_philo(table);
	return (0);
}
