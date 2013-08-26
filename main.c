
// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

void *runThread(void *ptr);

int main(int argc, char** argv)
{
 printf("Hello world\n");
 int i; 
 int numberOfThreads = 40;
 pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t)*numberOfThreads);
 for(i = 0; i < numberOfThreads; i++)
    {
      //pthread_create( (threads+i), NULL, runThread, (void*)threads);
    }
 
 pthread_mutex_lock(threads);
}

void *runThread(void *ptr)
{
 printf("Hello");
}
