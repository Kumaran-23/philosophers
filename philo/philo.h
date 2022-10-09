/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snair <snair@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:08:52 by snair             #+#    #+#             */
/*   Updated: 2022/10/09 12:41:25 by snair            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# define ALIVE 0
# define DEAD 1

# define EC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define YELLOW	"\e[33m"

typedef struct s_philo
{
	int				id;
	long int		last_ate;
	int				all_ate;
	int				fork_left;
	int				fork_right;
	long int		start_time;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				life_status;
	int				eat_num;
	int				philo_num;
	pthread_t		thread;
	pthread_mutex_t	*eat_time;
	pthread_mutex_t	*eat_amount;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*msg;
}t_philo;

typedef struct s_global
{
	int				philo_num;
	long int		time_die;
	long int		time_sleep;
	long int		time_eat;
	int				eat_num;
	long int		start_time;
	pthread_t		check;
	pthread_mutex_t	eat_time;
	pthread_mutex_t	eat_amount;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	msg;
	t_philo			*philo;
}t_global;

typedef enum e_status
{
	FORK_1 = 1,
	FORK_2 = 2
}				t_status;

/*utils*/
int					error(char *message);
void				print_log(t_philo philo, char *message, char *colour);
void				print_fork(t_philo philo, char *str, t_status status);

/*get_time*/
unsigned long int	current_time_ms(void);
void				time_spent(unsigned long time);

/*init*/
int					init_table(t_global *table, char **argv);

/*routine*/
void				*philo_life(void *arg);

/*death_eat_check*/
int					meal_count(t_philo *philo);
int					check_death(t_philo *philo);
void				*check_routine(void *arg);

/*free_destroy*/
void				free_all(t_global *table);

/*error_check*/
void				print_error(int num);
int					ft_atoi(const char *str);
int					arg_check(t_global *table, char **argv);

/*main*/
void				threads_create(t_global *table);

#endif