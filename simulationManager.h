#ifndef simulationmanager_h 
#define simulationmanager_h 

#include <pthread.h> 
#include "config.c" 
#include "world.h"
#include "simulationManager_thread_control.h"
typedef struct simulationManager
{
 world w;
 pthread_t threads[NUMBER_OF_THREADS];
 simulationManager_thread_control threadControls[NUMBER_OF_THREADS];
} simulationManager; 


#endif
