#ifndef PHILOO_H
#define PHILOO_H

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

typedef struct s_mutexes
{
    pthread_mutex_t print;
    pthread_mutex_t belly;
    pthread_mutex_t dead;
    pthread_mutex_t die_mutex;
    pthread_mutex_t get_time;
}t_mut;

typedef struct s_philinf
{
    pthread_mutex_t print;
    int number_philos;
    int time_die;
    int time_eat;
    int time_sleep;
    int n_must_eat;
    int  is_full;
    int is_dead;
    t_philo *phi;
    t_mut *mutexes;
    int stop_eat;
}t_philinf;

typedef struct s_philo
{
    pthread_t th_philo;
    int id_philo;
    long born;
    long add_time;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_philinf *tba;
    int kerchek;
    int n_must_eat;
    long last_meal;
    long time_func;
    int time_to_eating;
    int time_to_sleepy;
    int time_too_die;

}t_philo;


#endif