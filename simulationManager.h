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

void simulationManager_setupThreads(simulationManager *sm);
void simulationManager_cleanupThreads(simulationManager *sm);
void simulationManager_seedAgents(simulationManager *sm);
void simulationManager_runAgentDecisions(simulationManager *sm); //Single-threaded
void simulationManager_runAgentActions(simulationManager *sm); //Multi-threaded
void simulationManager_runIterations(simulationManager *sm, int iterations, int seedInterval, int seedDuration);
void simulationManager_runIntelligenceTests(simulationManager *sm);
void simulationManager_run(simulationManager *sm);

#endif
