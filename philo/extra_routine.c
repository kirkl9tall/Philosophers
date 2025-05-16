/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:20 by abismail          #+#    #+#             */
/*   Updated: 2025/05/16 16:28:11 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->tba->mutexes->die_mutex);
	if (philo->tba->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->tba->mutexes->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->tba->mutexes->die_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	usleep(1000);
	if (phi->id_philo % 2 != 0)
		usleep (1000);
	while (!check_obesity(phi) && !is_dead(phi))
	{
		if (eating(phi))
			break ;
		if (sleeping(phi))
			break ;
		thinking(phi);
	}
	return (NULL);
}

int	init_mutex(t_philinf *tb)
{
	if (pthread_mutex_init(&tb->mutexes->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&tb->mutexes->belly, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&tb->mutexes->die_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&tb->mutexes->get_time, NULL) != 0)
		return (1);
	return (0);
}

void	print_death(t_philo *phi, char *str)
{
	pthread_mutex_lock(&phi->tba->mutexes->print);
	printf("%ld\t%d\t%s\n", (get_time() - phi->born), phi->id_philo, str);
	pthread_mutex_unlock(&phi->tba->mutexes->print);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->tba->number_philos)
	{
		pthread_mutex_lock(&philo->tba->mutexes->get_time);
		pthread_mutex_lock(&philo->tba->mutexes->belly);
		if (((get_time() - philo[i].last_meal) >= philo[i].time_too_die)
			&& philo[i].last_meal != 0)
		{
			pthread_mutex_unlock(&philo->tba->mutexes->belly);
			pthread_mutex_lock(&philo->tba->mutexes->die_mutex);
			philo[i].tba->is_dead = 1;
			pthread_mutex_unlock(&philo->tba->mutexes->die_mutex);
			pthread_mutex_unlock(&philo->tba->mutexes->get_time);
			print_death(&philo[i], "is die");
			return (1);
		}
		pthread_mutex_unlock(&philo->tba->mutexes->belly);
		pthread_mutex_unlock(&philo->tba->mutexes->get_time);
		i++;
	}
	return (0);
}
