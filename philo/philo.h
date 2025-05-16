/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:01:50 by abismail          #+#    #+#             */
/*   Updated: 2025/05/13 17:38:51 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_mutexes
{
	pthread_mutex_t		print;
	pthread_mutex_t		belly;
	pthread_mutex_t		die_mutex;
	pthread_mutex_t		get_time;
}						t_mut;

typedef struct s_philinf
{
	pthread_mutex_t		print;
	int					number_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					n_must_eat;
	int					is_full;
	int					is_dead;
	t_philo				*phi;
	t_mut				*mutexes;
	int					stop_eat;
}						t_philinf;

typedef struct s_philo
{
	pthread_t			th_philo;
	int					id_philo;
	long				born;
	long				add_time;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_philinf			*tba;
	int					kerchek;
	int					n_must_eat;
	long				last_meal;
	long				time_func;
	int					time_to_eating;
	int					time_to_sleepy;
	int					time_too_die;

}						t_philo;

int						atoi_check(char nptr, int signe, int num);
int						ft_atoi(const char *nptr);
int						abs_args(int argc, char *argv[], t_philinf *tb);
long					get_time(void);
void					print_event(t_philo *phi, char *str);
int						pick_forks(t_philo *phi);
int						eating(t_philo *phi);
int						sleeping(t_philo *phi);
void					thinking(t_philo *phi);
int						check_obesity(t_philo *phi);
int						is_dead(t_philo *philo);
void					print_death(t_philo *phi, char *str);
void					*routine(void *arg);
int						init_mutex(t_philinf *tb);
int						check_death(t_philo *philo);
void					*monitor(void *arg);
void					destroy_mutex(t_philinf *tb);
void					create_n_join(t_philinf *tb, t_philo *phi,
							pthread_mutex_t *forks);
int						init_philo(t_philinf *tb, t_philo *phi,
							pthread_mutex_t *forks);
void					init_flags(t_philinf *tb);
int						philo_born(t_philinf *tb, t_philo *phi,
							pthread_mutex_t *forks);
void					freeing(t_philinf *tab, t_philo *phi,
							pthread_mutex_t *forks);
int						ft_is_alpha(int x);
#endif