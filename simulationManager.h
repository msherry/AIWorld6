#ifndef simulationmanager_h 
#define simulationmanager_h 

#include <pthread.h> 
#include "config.c" 

typedef struct simulationManager
{
 world w;
 agent agents[WORLD_SIZE*WORLD_SIZE];
 bool agentInUse[WORLD_SIZE*WORLD_SIZE];
 pthread_t* threads[NUMBER_OF_THREADS];

} simulationManager; 


#endif
