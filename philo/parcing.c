/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:48 by abismail          #+#    #+#             */
/*   Updated: 2025/05/13 17:33:07 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_check(char nptr, int signe, int num)
{
	if (signe == 1 && (num > INT_MAX / 10 || (num == INT_MAX / 10 && (nptr
					- '0') > INT_MAX % 10)))
		return (0);
	else if (signe == -1 && (num > (long)INT_MAX / 10 || (num == (long)INT_MAX
				/ 10 && (nptr - '0') > ((long)INT_MAX % 10 + 1))))
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	x;
	int	signe;
	int	num;

	x = 0;
	signe = 1;
	num = 0;
	while (nptr[x] == '\t' || nptr[x] == ' ' || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == '+' || nptr[x] == '-')
		if (nptr[x++] == '-')
			signe *= -1;
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		if (!(atoi_check(nptr[x], signe, num)))
			return (-1);
		num = num * 10 + (nptr[x++] - '0');
	}
	if (ft_is_alpha(nptr[x]))
		return (-1);
	return (num * signe);
}

int	abs_args(int argc, char *argv[], t_philinf *tb)
{
	tb->number_philos = ft_atoi(argv[1]);
	tb->time_die = ft_atoi(argv[2]);
	tb->time_eat = ft_atoi(argv[3]);
	tb->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		tb->n_must_eat = ft_atoi(argv[5]);
	else
		tb->n_must_eat = INT_MAX;
	if (tb->number_philos < 0 || tb->time_die < 0 || tb->time_eat < 0
		|| tb->time_sleep < 0 || tb->n_must_eat < 0)
	{
		free(tb->mutexes);
		free(tb);
		return (1);
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_event(t_philo *phi, char *str)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return ;
	pthread_mutex_lock(&phi->tba->mutexes->print);
	if (!(check_obesity(phi) || is_dead(phi)))
		printf("%ld\t%d\t%s\n", (get_time() - phi->born), phi->id_philo, str);
	pthread_mutex_unlock(&phi->tba->mutexes->print);
	return ;
}
