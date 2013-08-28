#ifndef SIMULATIONMANAGER_C
#define SIMULATIONMANAGER_C 
#include "simulationManager.h"

void simulationManager_setupThreads(simulationManager sm);
void simulationManager_runIterations(simulationManager sm, int iterations);

void simulationManager_run(simulationManager sm)
{
 printf("Running simuation of the world\n");
 //Load world, run all agent decisions, then act on all agent decisions, then do statistics gathering on this turn, then when it's all done do assessments

 world_createFromScratch(sm.w);
 simulationManager_setupThreads(sm);
 simulationManager_runIterations(sm, WORLD_ITERATIONS);
  
}

void simulationManager_setupThreads(simulationManager sm)
{
 printf("did nothing to setup threads\n");
}

void simulationManager_runIterations(simulationManager sm, int iterations)
{
 printf("did nothing to run iterations\n");
}
#endif
