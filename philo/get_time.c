/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:09:31 by snair             #+#    #+#             */
/*   Updated: 2022/10/04 12:09:34 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*function to calculate time in miliseconds*/
unsigned long int	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*while current time is less than wake usleep is called untill 
current time equals wake*/
void	time_spent(unsigned long time)
{
	unsigned long	wake;

	wake = current_time_ms() + time;
	while (current_time_ms() < wake)
		usleep(100);
}