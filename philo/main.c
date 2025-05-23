/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:42 by abismail          #+#    #+#             */
/*   Updated: 2025/05/13 17:40:03 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_alpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'z'))
		return (1);
	return (0);
}

int	philo_born(t_philinf *tb, t_philo *phi, pthread_mutex_t *forks)
{
	init_flags(tb);
	if (init_mutex(tb))
		return (1);
	if (init_philo(tb, phi, forks))
		return (1);
	create_n_join(tb, phi, forks);
	return (0);
}

void	freeing(t_philinf *tab, t_philo *phi, pthread_mutex_t *forks)
{
	free(phi);
	free(tab->mutexes);
	free(tab);
	if (forks)
		free(forks);
}

int	main(int argc, char *argv[])
{
	t_philinf		*tab;
	pthread_mutex_t	*forks;
	t_philo			*phi;

	if (argc == 5 || argc == 6)
	{
		phi = NULL;
		tab = malloc(sizeof(t_philinf));
		tab->mutexes = malloc(sizeof(t_mut));
		if (abs_args(argc, argv, tab))
			return (0);
		phi = malloc(tab->number_philos * sizeof(t_philo));
		if (!phi)
			return (freeing(tab, phi, NULL), 1);
		forks = malloc(tab->number_philos * sizeof(pthread_mutex_t));
		if (!forks)
			return (freeing(tab, phi, forks), 1);
		if (philo_born(tab, phi, forks))
			freeing(tab, phi, forks);
		freeing(tab, phi, forks);
	}
	return (0);
}
