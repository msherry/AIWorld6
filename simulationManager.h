#ifndef simulationmanager_h 
#define simulationmanager_h 
#include <pthread.h> 
#include "config.c" 
#include "world.h"
#include "simulationManager_thread_control.h"
typedef struct simulationManager
{
 int i;
 world w;
 double speed, speedDecision, speedAction, speedSeed;
 pthread_t threads[NUMBER_OF_THREADS];
 simulationManager_thread_control threadControls[NUMBER_OF_THREADS];
} simulationManager; 

void simulationManager_setupThreads();
void simulationManager_cleanupThreads();
void simulationManager_seedAgents();
void simulationManager_runAgentDecisions(); //Single-threaded
void simulationManager_runAgentActions(); //Multi-threaded
void simulationManager_runIterations(int iterations, int seedInterval, int seedDuration);
void simulationManager_runIntelligenceTests();
void simulationManager_run();

#endif
