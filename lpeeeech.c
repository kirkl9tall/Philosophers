long get_time()
{
	struct timeval tv;

	gettimeofday(&tv , NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec /1000);
}

void 	print_event(t_philo *phi , char *str)
{
	pthread_mutex_lock(&phi->tba->print);
	printf("%ld\t%d\t%s\n" , (get_time() - phi-> born) , phi->id_philo , str);
	pthread_mutex_unlock(&phi->tba->print);

}
void eating(t_philo *phi)
{
	if (check_obesity(phi) == 1)
		return;
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
		pthread_mutex_lock(phi->r_fork);
		print_event(phi , "has taken a fork");
	}
	pthread_mutex_lock(&phi->tba->mutexes->get_time);
	phi->last_meal = get_time();
	pthread_mutex_unlock(&phi->tba->mutexes->get_time);
	print_event(phi,"is eating");
	usleep(phi->time_to_sleepy*1000);
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	phi->kerchek++;
	pthread_mutex_lock(&phi->tba->mutexes->belly);
	if (phi->kerchek == phi->tba->n_must_eat)
		phi->tba->is_full++;
	pthread_mutex_unlock(&phi->tba->mutexes->belly);
}
void sleeping (t_philo *phi)
{
	if (check_obesity(phi) == 1)
		return;
	print_event(phi,"is sleeping");
	usleep(phi->time_to_sleepy*1000);
}

void thinking(t_philo *phi)
{
	if (check_obesity(phi) == 1)
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
void* routine(void *arg)
{
    t_philo *phi;
	phi = (t_philo*)arg;
	usleep(6000);
	while (check_obesity(phi) != 1)
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

void* monitor(void* arg)
{
	t_philinf *tb = (t_philinf *)arg;
	while (1)
	{
		pthread_mutex_lock(&tb->mutexes->belly);
		if (tb->is_full == tb->number_philos)
			{
				tb->stop_eat = 1;
				pthread_mutex_unlock(&tb->mutexes->belly);
				break;
			}
		pthread_mutex_unlock(&tb->mutexes->belly);
		usleep(1000);
	}
	usleep(9000);
	return NULL;
}
void create_n_join(t_philinf *tb,t_philo *phi,pthread_mutex_t *forks)
{
	int i = 0;
	long start;
	pthread_t moni;

	pthread_create(&moni,NULL,&monitor,tb);
	start = get_time();
	while (i < tb->number_philos){
		phi[i].born = start;	
		pthread_create(&phi[i].th_philo,NULL,&routine,&phi[i]);
		i++;
	}
	i = 0;
	pthread_join(moni,NULL);
	while (i < tb->number_philos)
	{
		pthread_join(phi[i].th_philo,NULL);
		i++;
	}
	i = 0;
	while (i < tb->number_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&tb->mutexes->print);
	pthread_mutex_destroy(&tb->mutexes->belly);
	pthread_mutex_destroy(&tb->mutexes->die_mutex);
	pthread_mutex_destroy(&tb->mutexes->get_time);
}

void init_philo(t_philinf *tb,t_philo *phi,pthread_mutex_t *forks)
{	
	int i = 0;
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
	init_philo(tb,phi,forks);
	init_mutex(tb);
	create_n_join(tb,phi,forks);

	pthread_mutex_destroy(&tb->mutexes->print);
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
    abs_args(argc,argv,tab);
    phi = malloc (tab->number_philos * sizeof(t_philo));
	if(phi == NULL)
		return 1;
	forks = malloc(tab->number_philos*sizeof(pthread_mutex_t));
	if (!forks)
		return 1;
 	philo_born(tab,phi,forks);
	free(phi);
	free(tab->mutexes);
	free(tab);
	free(forks);
  }
  else
	printf("error d'usage\n");
}