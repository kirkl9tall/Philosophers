/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:27 by abismail          #+#    #+#             */
/*   Updated: 2025/05/05 11:45:40 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->tba->mutexes->belly);
		if (philo->tba->is_full == philo->tba->number_philos)
		{
			philo->tba->stop_eat = 1;
			pthread_mutex_unlock(&philo->tba->mutexes->belly);
			break ;
		}
		pthread_mutex_unlock(&philo->tba->mutexes->belly);
		if (check_death(philo) == 1)
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	destroy_mutex(t_philinf *tb)
{
	pthread_mutex_destroy(&tb->mutexes->print);
	pthread_mutex_destroy(&tb->mutexes->belly);
	pthread_mutex_destroy(&tb->mutexes->die_mutex);
	pthread_mutex_destroy(&tb->mutexes->get_time);
}

void	create_n_join(t_philinf *tb, t_philo *phi, pthread_mutex_t *forks)
{
	int			i;
	long		start;
	pthread_t	moni;

	i = 0;
	pthread_create(&moni, NULL, &monitor, phi);
	start = get_time();
	while (i < tb->number_philos)
	{
		phi[i].born = start;
		pthread_mutex_lock(&tb->mutexes->get_time);
		phi[i].last_meal = get_time();
		pthread_mutex_unlock(&tb->mutexes->get_time);
		pthread_create(&phi[i].th_philo, NULL, &routine, &phi[i]);
		i++;
	}
	pthread_join(moni, NULL);
	i = 0;
	while (i < tb->number_philos)
		pthread_join(phi[i++].th_philo, NULL);
	i = 0;
	while (i < tb->number_philos)
		pthread_mutex_destroy(&forks[i++]);
}

void	init_philo(t_philinf *tb, t_philo *phi, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	tb->is_full = 0;
	while (i < tb->number_philos)
	{
		phi[i].id_philo = i + 1;
		phi[i].tba = tb;
		phi[i].r_fork = &forks[i];
		phi[i].time_to_eating = tb->time_eat;
		phi[i].time_too_die = tb->time_die;
		phi[i].time_to_sleepy = tb->time_sleep;
		phi[i].kerchek = 0;
		if (i + 1 < tb->number_philos)
			phi[i].l_fork = &forks[i + 1];
		else
			phi[i].l_fork = &forks[0];
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_flags(t_philinf *tb)
{
	tb->is_dead = 0;
	tb->is_full = 0;
	tb->stop_eat = 0;
}
