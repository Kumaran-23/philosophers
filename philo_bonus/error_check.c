/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:11:04 by snair             #+#    #+#             */
/*   Updated: 2022/10/06 08:55:45 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isdigits(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		if (str[i + 1] == '-' || str[i + 1] == '+')
			sign = 0;
		i++;
	}
	if (isdigits(str) != 0)
		return (-1);
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (sign * res);
}

void	print_error(int num)
{
	if (num == 1)
		printf("Only positive numbers are valid and values below MAX INT\n");
	else if (num == 2)
	{
		printf("Argument format:\n");
		printf("./philo number_of_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep");
		printf(" (optional)number_of_times_each_philosopher_must_eat\n");
	}
}

int	arg_check(t_global *table, char **argv)
{
	if (table->philo_num <= 0 || table->time_die <= 0
		|| table->time_eat <= 0 || table->time_sleep <= 0)
	{
		print_error(1);
		return (1);
	}
	if (argv[5] && (table->eat_num <= 0 || table->eat_num > INT_MAX))
	{
		print_error(1);
		return (1);
	}
	if (table->philo_num > INT_MAX || table->time_die > INT_MAX
		|| table->time_eat > INT_MAX || table->time_sleep > INT_MAX)
	{
		print_error(1);
		return (1);
	}
	return (0);
}
