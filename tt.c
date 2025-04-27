// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h>

// int prime[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};


// void *routine(void *arg){
//     int index = *(int*)arg;
//     printf("%d \n",prime[index]);

// }
// int main(int argc, char *argv[])
// {
//     pthread_t th[10];

//     int i = 0 ;
//     while (i < 10)
//     {
//         if((pthread_create(&th[i],NULL,routine,&i))!=0){
//             perror("Error creating thread !");
//             return 1;
//         }
//         i++;
//     }   
//     i = 0;
//     while (i < 0){
//         pthread_join(th[i],NULL);
//         i++;
//     }
//     return 0;
// }


// void* val()
// {
//     int val = 5;
//     int *res = malloc (sizeof(int));
//     *res = val;
//     return (void*)res;
// }void* val()
// {
//     int val = 5;
//     int *res = malloc (sizeof(int));
//     *res = val;
//     return (void*)res;
// }

// int main ()
// {
//     pthread_t t1;

//     int *res;

//     if (pthread_create(&t1,NULL,&val,NULL) !=0)
//     {
//         perror("Error  creating the thread !");
//         return 1;
//     }
//     pthread_join(t1,(void**)&res);

//     printf("return value is : %d\n",*res);

// }
//     pthread_t t1;

//     int *res;

//     if (pthread_create(&t1,NULL,&val,NULL) !=0)
//     {
//         perror("Error  creating the thread !");
//         return 1;
//     }
//     pthread_join(t1,(void**)&res);

//     printf("return value is : %d\n",*res);

// }


// void *salam()
// {   
//     printf("salam !\n");
//     return NULL;
// }

// int main ()
// {
//     int i = 0; 
//     pthread_t t1;

//     pthread_create(&t1,NULL,&salam,NULL);
    
//     pthread_join(t1,NULL);
//     i = 5;
//     printf(" the number is  : %d\n",i);
// }


// int primes[10] = {2,3,5,7,11,13,17,19,23,29};

// void* routine (void* arg)
// {
//     sleep(1);
//     int index  = *(int*)arg;
//     printf("%d\n", index);
//     free(arg);

// }
// int main  ()
// {
//     pthread_t th[10];

//     int i = 0;
//     while (i < 10)
//     {
//         int* a = malloc(sizeof(int));
//         *a = i;
//         if(pthread_create(&th[i],NULL,&routine,a)!=0)
//         {
//             perror("Error creating the  thread !");
//             return 1;
//         }
//         i++;
//     }
//     int y = 0;
//     while (y < 10)
//     {
//         pthread_join(th[y],NULL);
//         y++;
//     }

// }



// typedef struct s_list
// {
//     int data;
//     struct s_list *next;
// }t_list;

// #include "ft_list.h"

// int             ft_list_size(t_list *begin_list)
// {
//     int         i = 0;
//     while (begin_list)
//     {
//         begin_list = begin_list->next;
//         i++;
//     }
//     return (i);
// }


// int main  ()
// {

//     t_list *head;
//     t_list *tail;

//     int i = 0;
//     while (i < 6)
//     {
//         t_list *l;
//         l = malloc(sizeof(t_list));
//         l->data = 0;
//         l->next = NULL;
//         		if (head == NULL)
// 		{
// 			head = l;
// 			tail = l;
// 		}
// 		else#include <stdio.h>

// 		{
// 			tail->next = l;
// 			tail = l;
// 		}
//         i++;
//     }
//     t_list *s;
//     s = head;
//         while (s)
//         {
//             printf("[%d]--",s->data);
//             s = s->next;
//         }
// }


// int main (int argc, char* argv[])
// {
//     if (argc == 2)
//     {
//         int  i = 0;

//         while (argv[1][i])
//         {   
//             if (argv[1][i] >= 'a' || argv[1][i] >= 'z')
//             {
//                 int times  = argv[1][i]

//             }
//         }


//     }


// }

// int j = 0;

// void *soso()
// {
//     int i = 0;

//     while ( i < 1000000)
//     {
//         i++;
//         j++;
//     }
// }


// void* roll_dice(void *args)
// {
//     int i = *((int *)args);
//     int *khi = malloc(sizeof(int));

//     while (i < 10)
//     {
//         i++;
// 	    printf("[%d]\n", i);
//     }
//     *khi = i;
//     return ((void *)khi);
// }
// int main ()
// {
//     int i = 0;

//     pthread_t th[5];
//     int j = 0;
//     void* res = 0;
//     int final = 0;
//     while (i < 5)
//     {
//         pthread_create(&th[i],NULL,&roll_dice,&j);
//         i++;
//     }
//     i = 0;
//     while (i < 5)
//     {
//         pthread_join(th[i], &res);
//         final += *((int *)res);
//    	    printf("%d\n", final);
// 	    printf("\n+++++++++++++++++++++\n");
//         i++;
//     } 
//    // printf("%ld\n", (double *)res);
//    // printf("%d\n", j);
// }


// void* thread_func(void* arg) {
    
//     pthread_exit((void*)100);
// }
// #include "philo.h"

// int main() {

//         struct timeval tv;
        
//         int i = 0; 
//         int j = 0;

//         gettimeofday(&tv,NULL);
//         i = tv.tv_usec;
//         printf("time is [%d]\n",i);
//         gettimeofday(&tv,NULL);
//         j = tv.tv_usec;
//         printf("time is [%d]\n",j);
//         printf("the time  passed btween the two capture  is  [%d]\n",j-i);
//     return 0;
// }

// void lolo(pthread_mutex_t *forks)
// {
//     int i = 0;
// 	while(i < 5)
// 	{
// 		printf("[%p]\n", forks++);    struct timeval time;
//     gettimeofday(&time,NULL);
//     long s = time.tv_sec;
//     printf("current time is  %ld \n",time.tv_sec);
//     while(1)
//     {
//         gettimeofday(&time,NULL);
//         long j = time.tv_sec;
//         if(j > s + 5)
//         {
//             printf("dazat 5 s\n");
//             break;
//         }
//     }

//     while (i < 5)
//     {
//         printf("{%p}\n",forks+i);
//         i++;
//     }

// }

// struct timeval {
//                time_t      tv_sec;     /* seconds */
//                suseconds_t tv_usec;    /* microseconds */
//            };


// int gettimeofday(struct timeval *tv, struct timezone *tz);

// #include <sys/time.h>


// void *kayakol(void *i)
// {
//     struct timeval time;
//     gettimeofday(&time,NULL);
//     long x = 0;
//     x = time.tv_usec;
//     printf("[%d]\n",*(int*)i);
//     int *y = (int*)i;
//     while (*y < 10)
//     {
//         (*y)++;
//         printf("[%d]\n",*y);
//     }
//     usleep (500);
//     int *z = malloc (sizeof(int));
//     gettimeofday(&time,NULL);
//     long j = 0;void doli(void *arg)
// {
        
//     printf("hello i am %s\n",(char *)arg);
//     usleep(100000);
// }
// void doli1(void *arg)
// {

//     printf("second  pop  %s\n",(char *)arg);
//     usleep(100000);
// }
// void *fun1(void* arg)
// {

//     sleep (1);
// printf("hello  i am thread  2  !\n");
//    return NULL;
// }
//     j = time.tv_usec;
//    // printf("we did  [%ld] microsec in this function\n",(j-x));
//     *z = j-x;
//     return ((void*)z);
// }

// int main ()
// {   


//     pthread_t th;
//     int i = 5;
//     pthread_create(&th,NULL,kayakol,(void*)&i);

    
//     int *y = malloc (sizeof(int));
//     pthread_join(th,(void*)&y);
//     printf("time  done in this routine is   = %d\n",*y);

// }

// int main ()
// {
//     struct timeval start, end;
    
//     gettimeofday(&start,NULL);
//     usleep(150);
//     gettimeofday(&end,NULL);
//     long time_taken;
//     time_taken = (end.tv_sec-start.tv_sec);
//     time_taken = (time_taken + (end.tv_usec-start.tv_usec));

//     printf("\e[31mThe time taken  to sleep was : [%ld]\n\e[0m",time_taken);
// }


// void flood_fill (char **map, int x , int y) 
// {
//     if(map[x][y]== 'x')
//         return;
//     flood_fill(map,x+1,y);
//     flood_fill(map,x-1,y);
//     flood_fill(map,x,y+1);
//     flood_fill(map,x,y-1);
// }


// int main() {
//    int array[10] = {1, 2, 3, 4, 5, -1, 7, 8, 9, 0};
//    int loop, smallest;

//    smallest = array[0];
   
//    for(loop = 1; loop < 10; loop++) {
//       if( smallest > array[loop] ) 
//          smallest = array[loop];
//    }
   
//    printf("Smallest element of array is %d\n ", smallest);   
   
//    return 0;
// }

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>
#include <math.h>
// void cleanup(void *arg) {
//     printf("Cleanup handler called: %s\n", (char *)arg);

// }

// void *fun(void *arg) {
    //     pthread_cleanup_push(cleanup, arg);
    
    //     printf("thread started\n");
    
    //     // Simulate some work
    //     sleep(1);
    
    //     // Optional: cancel point
    //    // pthread_testcancel(); // This gives the thread a chance to be canceled here
    // //    pthread_exit(NULL);
    //    pthread_cleanup_pop(1); // 1 means: call the cleanup function now
    //     return NULL;
    // }
    // pthread_t th1;
    
// void doli(void *arg)
// {
        
//     printf("hello i am %s\n",(char *)arg);
//     usleep(100000);
// }
// void doli1(void *arg)
// {

//     printf("second  pop  %s\n",(char *)arg);
//     usleep(100000);
// }
// void *fun1(void* arg)
// {

//     sleep (1);
// printf("hello  i am thread  2  !\n");
//    return NULL;
// }

//int i = 0;
// void *fun(void* arg)
// {
//     //pthread_cleanup_push(doli,"thread");

//     usleep(100000);
//     printf("hello  i am thread  i will a new thread  %i\n", i++);
//    return NULL;
// }
// void *fun(void *arg)
// {
//     int io = 0;
//     while(io != 1200)
//     {
//         usleep(1000);
//         if(i == 0)
//         {
//             // i++;
//             io++;
//         }
//     }
//     return NULL;
// }
// int main() {

//     // printf("%p\n", th);
//     pthread_t th;
//     pthread_t th1;
//     pthread_create(&th, NULL, fun, NULL);
//     pthread_create(&th1, NULL, fun, NULL);
//     // usleep(10000);
//     //    usleep(100000);
//     pthread_join(th,NULL); // Wait for the thread to finish 
//     pthread_join(th1,NULL);
//     // printf("error number : %d\n",pthread_join(th,NULL));
//     // pthread_exit(0);
    
// }


// typedef struct s_test
// {
//     pthread_t th;
//     int id_th;
//     long start;
//     int time_to_die;
//     long  all;

// }t_test;


// long get_time(){

//     struct timeval time;
//     gettimeofday(&time,NULL);
//     return ((time.tv_sec * 1000 ) + (time.tv_usec)/1000); 
// }

// void eat(t_test * philo){
//    // printf("I am philo number %d   I am eating \n",philo->id_th);
//     usleep(100000);
// }
// void sleeping(t_test * philo){
//     //printf("I am philo number %d   I am sleeping  \n",philo->id_th);
//     usleep(500000);
// }

// void think(t_test * philo){
//     //printf("I am philo number %d   I am thinking  \n",philo->id_th);
//     usleep(200000);
// }

// void* routine (void *arg)
// {   
//     t_test *philo;

//     philo = (t_test*)arg;
//     philo->id_th = 1;
//     philo->time_to_die = 502;
//     long capture;
//     long entire;
//     philo->all = 0;
//     while (1)
//     {
        
//         if (philo->all > philo->time_to_die)
//         break;
//         printf("\e[31mthe  entire diff   time : %ld \n\e[0m",philo->all);
//         philo->start = get_time();
//         think(philo);
//         capture = get_time();
//         printf("\e[31mthink  time : %ld \n\e[0m",philo->all = capture - philo->start);
//         ///
//         if (philo->all > philo->time_to_die)
//         break;
//         philo->start = get_time();
//         eat(philo);
//         capture = get_time();
//         printf("\e[32meat time : %ld \n\e[0m",philo->all += capture - philo->start);
//         /////
//         if (philo->all > philo->time_to_die)
//         break;
//         philo->start = get_time();
//         sleeping(philo);
//         capture = get_time();
//         printf("\e[33msleep time : %ld \n\e[0m",philo->all += capture - philo->start);
//     }


// }
// int main  ()
// {
//     t_test *philo;

//     philo = malloc(sizeof(t_test));
//     pthread_create(&philo->th,NULL,routine,philo);
//     pthread_join(philo->th,NULL);
// }


// int mails = 0;
// pthread_mutex_t mutex;
// pthread_mutex_t mutex1;


// void* routine (void* arg)
// {
//     int a  = 0;
//     while (a < 10000000)
//     {   
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
//         a++;
//     }
//     return (NULL);
// }
// void* routine1 (void* arg)
// {
//     int a  = 0;
//     while (a < 10000000)
//     {   
//         pthread_mutex_lock(&mutex1);
//         mails++;
//         printf("mails %d\n",mails);
//         pthread_mutex_unlock(&mutex1);
//         a++;
//     }
//     return (NULL);
// }
// int main  ()
// {
//     pthread_t th,th1 ;
    
//     pthread_create(&th,NULL,routine,NULL);
//     pthread_create(&th1,NULL,routine1,NULL);
//     pthread_join(th,NULL);
//     pthread_join(th1,NULL);

//     printf ("mails  = %d\n",mails);

// }
