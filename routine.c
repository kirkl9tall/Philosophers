/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:52 by abismail          #+#    #+#             */
/*   Updated: 2025/04/30 10:48:58 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_forks(t_philo *phi)
{
	if (phi->id_philo % 2 == 0)
	{
		pthread_mutex_lock(phi->r_fork);
		print_event(phi, "has taken a fork");
		pthread_mutex_lock(phi->l_fork);
		print_event(phi, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phi->l_fork);
		print_event(phi, "has taken a fork");
		if (phi->tba->number_philos == 1)
		{
			pthread_mutex_unlock(phi->l_fork);
			return (1);
		}
		pthread_mutex_lock(phi->r_fork);
		print_event(phi, "has taken a fork");
	}
	return (0);
}

int	eating(t_philo *phi)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return (1);
	if (pick_forks(phi) == 1)
		return (1);
	pthread_mutex_lock(&phi->tba->mutexes->get_time);
	phi->last_meal = get_time();
	pthread_mutex_unlock(&phi->tba->mutexes->get_time);
	print_event(phi, "is eating");
	usleep(phi->time_to_eating * 1000);
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	phi->kerchek++;
	pthread_mutex_lock(&phi->tba->mutexes->belly);
	if (phi->kerchek == phi->tba->n_must_eat)
		phi->tba->is_full++;
	pthread_mutex_unlock(&phi->tba->mutexes->belly);
	return (0);
}

void	sleeping(t_philo *phi)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return ;
	print_event(phi, "is sleeping");
	usleep(phi->time_to_sleepy * 1000);
}

void	thinking(t_philo *phi)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return ;
	print_event(phi, "is thinking");
	usleep(1000);
}

int	check_obesity(t_philo *phi)
{
	pthread_mutex_lock(&phi->tba->mutexes->belly);
	if (phi->tba->stop_eat == 1)
	{
		pthread_mutex_unlock(&phi->tba->mutexes->belly);
		return (1);
	}
	pthread_mutex_unlock(&phi->tba->mutexes->belly);
	return (0);
}
