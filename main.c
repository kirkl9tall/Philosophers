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
		num = num * 10 + (nptr[x++] - '0');
	return (num * signe);
}

int abs_args(int argc,char *argv[],t_philinf *tb)
{
    tb->number_philos = ft_atoi(argv[1]);
    tb->time_die = ft_atoi(argv[2]);
    tb->time_eat  = ft_atoi(argv[3]);
    tb->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
      tb->n_must_eat = atoi(argv[5]);
	else 
		tb->n_must_eat = INT_MAX;
	if (tb->number_philos < 0|| tb->time_die < 0 ||
		 tb->time_eat < 0|| tb->time_sleep < 0|| tb->n_must_eat < 0)
		{
			free(tb->mutexes);
			free(tb);
			return 1;
		}
	return 0;
}
long get_time()
{
	struct timeval tv;

	gettimeofday(&tv , NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec /1000);
}

void 	print_event(t_philo *phi , char *str)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return;
	pthread_mutex_lock(&phi->tba->print);
	printf("%ld\t%d\t%s\n" , (get_time() - phi-> born) , phi->id_philo , str);
	pthread_mutex_unlock(&phi->tba->print);

}
int pick_forks(t_philo *phi)
{
	if(phi->id_philo % 2 == 0)
	{
		pthread_mutex_lock(phi->r_fork);
		print_event(phi , "has taken a fork");
		pthread_mutex_lock(phi->l_fork);
		print_event(phi , "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phi->l_fork);
		print_event(phi , "has taken a fork");
		if (phi->tba->number_philos == 1){
			pthread_mutex_unlock(phi->l_fork);
			return 1;
		}
		pthread_mutex_lock(phi->r_fork);
		print_event(phi , "has taken a fork");
	}
	return 0 ;
}
int eating(t_philo *phi)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return 1;
	if (pick_forks(phi) == 1)
		return 1;
	pthread_mutex_lock(&phi->tba->mutexes->get_time);
	phi->last_meal = get_time();
	pthread_mutex_unlock(&phi->tba->mutexes->get_time);
	print_event(phi,"is eating");
	usleep(phi->time_to_eating*1000);
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	phi->kerchek++;
	pthread_mutex_lock(&phi->tba->mutexes->belly);
	if (phi->kerchek == phi->tba->n_must_eat)
		phi->tba->is_full++;
	pthread_mutex_unlock(&phi->tba->mutexes->belly);
	return 0;
}
void sleeping (t_philo *phi)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return;
	print_event(phi,"is sleeping");
	usleep(phi->time_to_sleepy * 1000);
}

void thinking(t_philo *phi)
{
	if (check_obesity(phi) == 1 || is_dead(phi) == 1)
		return;
	print_event(phi,"is thinking");
	usleep (1000);
}
int check_obesity(t_philo* phi)
{
	pthread_mutex_lock(&phi->tba->mutexes->belly);
	if(phi->tba->stop_eat == 1)
	{
		pthread_mutex_unlock(&phi->tba->mutexes->belly);	
		return  1;
	}
	pthread_mutex_unlock(&phi->tba->mutexes->belly);
	return 0;
}
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
	//long measure = 0;
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
void* monitor(void* arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->tba->mutexes->belly);
		if (philo->tba->is_full == philo->tba->number_philos)
			{
				philo->tba->stop_eat = 1;
				pthread_mutex_unlock(&philo->tba->mutexes->belly);
				break;
			}
		pthread_mutex_unlock(&philo->tba->mutexes->belly);
		if(check_death(philo) == 1)
			break;
		if (philo->tba->number_philos == 1)
			break;
		usleep(1000);
	}
	return NULL;
}
void destroy_mutex(t_philinf *tb)
{
	pthread_mutex_destroy(&tb->mutexes->print);
	pthread_mutex_destroy(&tb->mutexes->belly);
	pthread_mutex_destroy(&tb->mutexes->die_mutex);
	pthread_mutex_destroy(&tb->mutexes->get_time);
}

void create_n_join(t_philinf *tb,t_philo *phi,pthread_mutex_t *forks)
{
	int i;
	long start;
	pthread_t moni;

	i = 0;
	pthread_create(&moni,NULL,&monitor,phi);
	start = get_time();
	while (i < tb->number_philos){
		phi[i].born = start;	
		pthread_create(&phi[i].th_philo,NULL,&routine,&phi[i]);
		i++;
	}
	pthread_join(moni,NULL);
	i = 0;
	while (i < tb->number_philos)
		pthread_join(phi[i++].th_philo,NULL);
	i = 0;
	while (i < tb->number_philos)
		pthread_mutex_destroy(&forks[i++]);
}

void init_philo(t_philinf *tb,t_philo *phi,pthread_mutex_t *forks)
{	
	int i;
	
	i = 0;
	tb->is_full = 0;
		while (i<tb->number_philos)
		{
			phi[i].id_philo = i+1;
			phi[i].tba = tb;
			phi[i].r_fork = &forks[i];
			phi[i].time_to_eating = tb->time_eat;
			phi[i].time_too_die = tb->time_die;
			phi[i].time_to_sleepy = tb->time_sleep;
			phi[i].kerchek = 0;
			if(i+1 < tb->number_philos)
				phi[i].l_fork = &forks [i+1] ;
			else 
				phi[i].l_fork = &forks[0] ;
			pthread_mutex_init(&forks[i],NULL);
			i++;
		}
}
void  init_flags(t_philinf* tb)
{
	tb->is_dead = 0;
	tb->is_full = 0;
	tb->stop_eat = 0;
}
void philo_born(t_philinf *tb,t_philo *phi,pthread_mutex_t *forks)
{
	init_flags(tb);
	init_mutex(tb);
	init_philo(tb,phi,forks);
	create_n_join(tb,phi,forks);
}
void freeing(t_philinf *tab,t_philo *phi, pthread_mutex_t *forks)
{
	free(phi);
	free(tab->mutexes);
	free(tab);
	free(forks);
}
int main (int argc, char *argv[])
{
  if (argc == 5  || argc == 6 )
  {
    t_philinf *tab;
	pthread_mutex_t *forks;
    t_philo *phi;
    phi = NULL;
    tab = malloc(sizeof(t_philinf));
	tab->mutexes = malloc(sizeof(t_mut));
    if (abs_args(argc,argv,tab))
		return 0;
    phi = malloc (tab->number_philos * sizeof(t_philo));
	if(!phi)
	{
		freeing(tab,phi,forks);
		return 1;
	}
	forks = malloc(tab->number_philos*sizeof(pthread_mutex_t));
	if (!forks)
	{
		freeing(tab,phi,forks);
		return 1;
	}
 	philo_born(tab,phi,forks);
	freeing(tab,phi,forks);
  }
  else
	printf("error d'usage\n");
}

/// comments  : 