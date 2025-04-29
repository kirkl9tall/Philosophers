#include "philo.h"

int is_dead(t_philo *philo)
{
		pthread_mutex_lock(&philo->tba->mutexes->die_mutex);
		if (philo->tba->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->tba->mutexes->die_mutex);	
			return 1;
		}	
		pthread_mutex_unlock(&philo->tba->mutexes->die_mutex);
		return 0;
}

void* routine(void *arg)
{
    t_philo *phi;
	phi = (t_philo*)arg;
	if (phi->tba->number_philos == 1)
	{
		print_death(phi,"is die");
		return (NULL);
	}
	while (!check_obesity(phi) && !is_dead(phi))
	{
		thinking(phi);
		eating(phi);
		sleeping(phi);
	}
    return NULL; 
}
void init_mutex(t_philinf *tb)
{
	pthread_mutex_init(&tb->mutexes->print, NULL);
	pthread_mutex_init(&tb->mutexes->belly, NULL);
	pthread_mutex_init(&tb->mutexes->die_mutex, NULL);
	pthread_mutex_init(&tb->mutexes->get_time, NULL);
}

void 	print_death(t_philo *phi , char *str)
{
	pthread_mutex_lock(&phi->tba->print);
	printf("%ld\t%d\t%s\n" , (get_time() - phi-> born) , phi->id_philo , str);
	pthread_mutex_unlock(&phi->tba->print);
}
int check_death(t_philo *philo)
{
	int i = 0;
	while(i < philo->tba->number_philos)
	{
		pthread_mutex_lock(&philo->tba->mutexes->get_time);
		if(((get_time() - philo[i].last_meal)) >= philo[i].time_too_die && philo[i].last_meal != 0)
		{
			pthread_mutex_lock(&philo->tba->mutexes->die_mutex);
			philo[i].tba->is_dead = 1;
			pthread_mutex_unlock(&philo->tba->mutexes->die_mutex);
			pthread_mutex_unlock(&philo->tba->mutexes->get_time);
			print_death(&philo[i],"is die");
			return (1);
		}
		pthread_mutex_unlock(&philo->tba->mutexes->get_time);
		i++;
	}
	return (0);
}
