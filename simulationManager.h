#ifndef simulationmanager_h 
#define simulationmanager_h 

#include <pthread.h> 
#include "config.c" 
#include "world.h"
typedef struct simulationManager
{
 world w;
 pthread_t* threads[NUMBER_OF_THREADS];

} simulationManager; 


#endif
