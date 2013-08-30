#ifndef SIMULATIONMANAGER_C
#define SIMULATIONMANAGER_C 
#include "simulationManager.h"
#include "simulationManager_thread.c"
#include <pthread.h>
void simulationManager_setupThreads(simulationManager sm);
void simulationManager_cleanupThreads(simulationManager sm);
void simulationManager_seedAgents(simulationManager sm);
void simulationManager_runAgentDecisions(simulationManager sm); //Single-threaded
void simulationManager_runAgentActions(simulationManager sm); //Multi-threaded
void simulationManager_runIterations(simulationManager sm, int iterations, int seedInterval, int seedDuration);
void simulationManager_runIntelligenceTests(simulationManager sm);
void simulationManager_run(simulationManager sm)
{
 printf("Running simuation of the world\n");
 //Load world, run all agent decisions, then act on all agent decisions, then do statistics gathering on this turn, then when it's all done do assessments

 world_createFromScratch(sm.w);
 simulationManager_setupThreads(sm);
 simulationManager_runIterations(sm, WORLD_ITERATIONS,SEED_INTERVAL,SEED_DURATION);
 simulationManager_runIntelligenceTests(sm);
 printf("done with intelligence tests");
 simulationManager_cleanupThreads(sm);
}

void simulationManager_setupThreads(simulationManager sm) {
 int i;
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  printf("didn't do anything to setup threads");
 }
}
void simulationManager_cleanupThreads(simulationManager sm) {
 int i;
 printf("cleaning threads");
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  printf("didn't do anything to clean up threads");
  //pthread_join( sm.threads[i], NULL);
 }
}

void simulationManager_runIterations(simulationManager sm, int iterations, int seedInterval, int seedDuration) {
 int i;
 for(i = 0; i < iterations; i++) {
  if(i % seedInterval == 0 && i < seedDuration)
   simulationManager_seedAgents(sm);
  simulationManager_runAgentDecisions(sm); //Single-threaded
  simulationManager_runAgentActions(sm); //Multi-threaded
 } 
}

void simulationManager_seedAgents(simulationManager sm) { 
 int i;
 i = 0;
 i++;
}

void simulationManager_signalThreadsToGo(simulationManager sm) {
 int i;
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  printf("didn't signal");//pthread_mutex_unlock(&(sm.threadControls[i].actionLock));//Releasing the worker threads to take action again
 }
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  printf("didn't signal"); //pthread_mutex_lock(&(sm.threadControls[i].actionLock));//Gather all the locks before anyone is allowed to do anything
 }
}

void simulationManager_runAgentDecisions(simulationManager sm) { //Single-threaded
 int i = 0;
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  sm.threadControls[i].runAgentDecision = 1; //The thread will turn it back to zero when done 
 }
 simulationManager_signalThreadsToGo(sm); 
}
void simulationManager_runAgentActions(simulationManager sm) { //Multi-threaded
 int i = 0;
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  sm.threadControls[i].runAgentAction = 1; //The thread will turn it back to zero when done 
 }
 simulationManager_signalThreadsToGo(sm); 
}

void simulationManager_runIntelligenceTests(simulationManager sm) {
 printf("did nothing to run intelligence tests\n");
}

#endif
