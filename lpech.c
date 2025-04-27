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
void abs_args(int argc,char *argv[],t_philinf *tb)
{
	tb->die = 0;
    tb->number_philos = ft_atoi(argv[1]);
    tb->time_die = ft_atoi(argv[2]);
    tb->time_eat  = ft_atoi(argv[3]);
    tb->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
      tb->n_must_eat = atoi(argv[5]);
	else 
		tb->n_must_eat = INT_MAX;
	if (tb->number_philos < 0||tb->time_die < 0 || tb->time_eat < 0|| tb->time_sleep < 0|| tb->n_must_eat < 0)
		{
			free(tb);
			exit(0);//?????????????
		}
}
long get_time()
{
	struct timeval tv;
	gettimeofday(&tv , NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec /1000);
}
int  check_philo(t_philo *phi);
void 	print_event(t_philo *phi , char *str)
{
	// if(check_philo(phi) == 1)
	// 	return;
	pthread_mutex_lock(&phi->tba->print);
	printf("%ld\t%d\t%s\n" , (get_time() -phi->start2) , phi->id_philo , str);
	pthread_mutex_unlock(&phi->tba->print);

}
int  check_philo(t_philo *phi)
{	
	pthread_mutex_lock(&phi->tba->belly);
	if (phi->tba->die == 1){
		pthread_mutex_unlock(&phi->tba->belly);
		return (1);
	}
	pthread_mutex_unlock(&phi->tba->belly);
	pthread_mutex_lock(&phi->tba->deadlook);
	if(phi->tba->stop == 1)
	{
		pthread_mutex_unlock(&phi->tba->deadlook);
		return (1);
	}
	pthread_mutex_unlock(&phi->tba->deadlook);


}
void eating(t_philo *phi)
{
	long time_taken;
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
	phi->last_meal = get_time();
	print_event(phi , "is eating");
	if (phi->tba->time_eat > phi->tba->time_die){
		usleep(phi->tba->time_die * 1000);
	}
	else 
	usleep(phi->tba->time_eat*1000); 
	pthread_mutex_unlock(phi->r_fork);
	pthread_mutex_unlock(phi->l_fork);
	pthread_mutex_lock(&phi->tba->belly);
	phi->kerchek++; //?
	phi->fligo = 1;
	if (phi->kerchek == phi->tba->n_must_eat)
		phi->tba->flag++;
	pthread_mutex_unlock(&phi->tba->belly);
}

void thinking(t_philo *phi)
{
	if(phi->id_philo % 2 == 1)
		usleep (1000);
	print_event(phi ,"is thinking");
}
void philo_sleep(t_philo *phi)
{
	print_event(phi ,"is sleeping");
	if (phi->tba->time_sleep > phi->tba->time_die){
		usleep(phi->tba->time_die * 1000);
	}
	else {
	usleep (phi->tba->time_sleep*1000);
	}
}

void* routine(void* arg)
{
	t_philo *phi;
	phi = (t_philo*)arg;
	long capture;
	phi->add_time = 0;
	while (1)
	{
		capture = get_time();
		if (check_philo(phi)== 1)
			break;
		thinking(phi);
		phi->time_func = get_time();
		phi->time_func -= capture;
		phi->add_time = phi->time_func;
		if (check_philo(phi)== 1)
			break;
		capture = get_time();
		eating(phi);
		phi->time_func = get_time();
		phi->time_func -= capture;
		if (check_philo(phi)== 1)
			break;
		capture = get_time();
		philo_sleep(phi);
		phi->time_func = get_time();
		phi->time_func -= capture;
		if (check_philo(phi)== 1)
			break;
	}
	return NULL;
}

void *monitor (void *arg)
{
	t_philinf *tb = (t_philinf*)arg;
	t_philo  **philo = tb->phi;
	int i =0;
	while (1)
	{
		if(i == tb->number_philos)
			i = 0;
		pthread_mutex_lock(&tb->belly);
		if (tb->flag == tb->number_philos)
			tb->stop = 1;
		pthread_mutex_unlock(&tb->belly);
		if (((get_time() - philo[i]->last_meal)  > tb->time_die ) && philo[i]->last_meal != 0)
		{
				print_event(philo[i] , "is died");
				tb->die = 1;
				break;
		}
		i++;	
		usleep(1000);
	}
}
void philo_born(t_philinf *tb,t_philo **phi,pthread_mutex_t *forks)
{
	int	i;
	pthread_t moni;
	long start;

	i = 0;
	tb->phi = phi;
	while (i < tb->number_philos)
	{
		phi[i] = malloc(sizeof(t_philo));
		phi[i]->id_philo = i+1;
		phi[i]->tba = tb;
		phi[i]->r_fork = &forks[i];
		phi[i]->fligo = 0;
		if(i+1 < tb->number_philos)
			phi[i]->l_fork = &forks [i+1] ;
		else 
			phi[i]->l_fork = &forks[0] ;
		pthread_mutex_init(&forks[i],NULL);
		i++;
	}
	pthread_create(&moni,NULL,&monitor,tb);
	pthread_mutex_init(&tb->print,NULL);
	pthread_mutex_init(&tb->belly,NULL);
	pthread_mutex_init(&tb->deadlook,NULL);
	i = 0;
	start = get_time();
	while (i < tb->number_philos){
		phi[i]->start2 = start;	
		pthread_create(&phi[i]->th_philo,NULL,&routine,phi[i]);
		i++;
	}
	i = 0;
	while (i < tb->number_philos)
	{
		pthread_join(phi[i]->th_philo,NULL);
		i++;
	}
	i = 0;
	while (i < tb->number_philos)
	{
	pthread_mutex_destroy(&forks[i]);
	i++;
	}
	pthread_mutex_destroy(&tb->deadlook);
	pthread_mutex_destroy(&tb->belly);
	pthread_mutex_destroy(&tb->print);
}

int main (int argc, char *argv[])
{
  if (argc == 5  || argc == 6 )
  {
    t_philinf *tb;
	pthread_mutex_t *forks;
    t_philo **phi = NULL;
    tb = malloc(sizeof(t_philinf));
	tb->flag = 0;
	tb->stop = 0;
    abs_args(argc,argv,tb);
    phi = malloc (tb->number_philos * sizeof(t_philo*));
	if(phi == NULL)
		return 1;
	forks = malloc(tb->number_philos*sizeof(pthread_mutex_t));
	int i = 0;
 	philo_born(tb,phi,forks);
	while (i <tb->number_philos)
		free(phi[i++]);
	free(phi);
	free(tb);
  }
  else
	printf("error d'usage\n");
}