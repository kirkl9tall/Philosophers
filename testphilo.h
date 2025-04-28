#ifndef PHILO_H
#define PHILO_H

#define number_of_philosophers
#define time_to_die
#define time_to_eat
#define time_to_sleep
#define number_of_times_each_philosopher_must_eat

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>
#include <math.h>

typedef struct s_philo t_philo;

typedef struct s_philinf
{
    int number_philos;
    int time_die;
    int time_eat;
    int time_sleep;
    int n_must_eat;
    int  flag;
    int stop;
    int die;
    t_philo **phi;
    pthread_mutex_t print;
    pthread_mutex_t belly;
    pthread_mutex_t die_mutex;
    pthread_mutex_t meals_lock;

    
}t_philinf;

typedef struct s_philo
{
    pthread_t th_philo;
    int id_philo;
    long start;
    long add_time;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_philinf *tba;
    int kerchek;
    int n_must_eat;
    long last_meal;
    long time_func;
    int fligo;
    int time_to_eating;
    int time_too_die;

}t_philo;

#endif