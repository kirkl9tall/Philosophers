#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>
#include <math.h>
// void *fun(void *ar)
// {
//    // while(1)
//         printf("thread\n");
// }
// int main()
// {
//     pthread_t th;

//     pthread_create(&th , NULL,fun , NULL);
//     // sleep(5);
//     pthread_detach(th);
//     // sleep(5);
//     pthread_cleanup_push(fun, NULL);
//     printf("=============\n");
// }

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void cleanup(void *arg) {
    printf("Cleanup handler called: %s\n", (char *)arg);

}

void *fun(void *arg) {
    pthread_cleanup_push(cleanup, "Thread resource");

    printf("thread started\n");

    // Simulate some work
    sleep(1);

    // Optional: cancel point
   // pthread_testcancel(); // This gives the thread a chance to be canceled here

    pthread_cleanup_pop(1); // 1 means: call the cleanup function now
    return NULL;
}

int main() {
    pthread_t th;

    pthread_create(&th, NULL, fun, NULL);
    sleep(1); // Wait a bit before canceling
   // pthread_cancel(th); // Ask the thread to cancel itself
    pthread_join(th, NULL); // Wait for the thread to finish

    printf("Main thread done\n");
    return 0;
}
///----------------------------------------------------------------------------------------------///


// void* fun(void *arg)
// {
//     printf("hello i am thread and i did run !\n");
//     //pthread_exit(NULL);

//     printf("here Iam  after the  pthread exit !!\n");
//     return NULL;
// }

// int main ()
// {

//     pthread_t th;

//     pthread_create(&th,NULL,fun,NULL);

//     pthread_join(th,NULL);


// }

// void * function(void*);

// int main()
// {
//     pthread_t thread;
//     int arg = 991;
//     int * status; // notice I did not intialize status, status is *retval
//     pthread_create(&thread, NULL, function, (void*)(&arg));

//     pthread_join(thread, (void **)(&status));//passing address of status,&status is retval 

//     //(2) this address is same as printed in (1)
//     printf("The address of returned status is %p, the arg adress is : %p ", status,&arg); 

//     printf("The returned status is %d\n", *status);
// }

// void * function(void * arg)
// {
//     int *p;
//     p = (int*)arg;
//     printf("I am in thread.\n");

//      //(1) printing the address of variable holding the exit status of thread, see (2)                                                              
//     printf("The arg address is %p %p\n", p, arg); 

//     pthread_exit(arg);
// }