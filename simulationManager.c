#ifndef SIMULATIONMANAGER_C
#define SIMULATIONMANAGER_C 
#include "simulationManager.h"
#include "simulationManager_thread.c"
#include "threadManager.c"
#include "simulationMonitor.c"
#include <pthread.h>
extern simulationManager sm;
void simulationManager_run()
{
 //Load world, run all agent decisions, then act on all agent decisions, then do statistics gathering on this turn, then when it's all done do assessments
 world_createFromScratch(&(sm.w));
 simulationManager_setupThreads();
 simulationManager_runIterations(WORLD_ITERATIONS,SEED_INTERVAL,SEED_DURATION);
 simulationManager_runIntelligenceTests();
 simulationManager_cleanupThreads();
}
void simulationManager_setupThreads() {
 int i;
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
   initThread(&(sm.threadControls[i]), &(sm.threads[i]), simulationManager_thread_run,i);
 }
}
void simulationManager_cleanupThreads() {
 int i;
 printf("cleaning threads");
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  printf("didn't do anything to clean up threads");
  //pthread_join( sm.threads[i], NULL);
 }
}

void simulationManager_runIterations(int iterations, int seedInterval, int seedDuration) {
 int i;
 for(i = 0; i < iterations; i++) {
  if(i % SIM_REPORT_INTERVAL == 0) {
   printf("Sim has performed %i intervals\n",i);
   simulationMonitor_emitMonitors();
  } 
  if(i % seedInterval == 0 && i < seedDuration)
   simulationManager_seedAgents();
  simulationManager_runAgentDecisions(); //Multi-threaded
  simulationManager_runAgentActions(); //Single-threaded
 } 
}

void simulationManager_seedAgents() { 
 int i,j;
 for(i = WORLD_BORDER; i < 30; i += 2) {
  for(j = WORLD_BORDER; j < 30; j += 2) {
   agent_mallocAgent_fromScratch(i,j,SEED_ENERGY);
  }
 } 
}

void simulationManager_signalThreadsToGo() {
 int i;
 for(i = 0; i < NUMBER_OF_THREADS; i++)  {
   notifyChildOfWorkToDo(&(sm.threadControls[i])); //This will *not* block
 }
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
   blockOnChildFinishingWork(&(sm.threadControls[i]));  //This will block
 }
}

void simulationManager_runAgentDecisions() { //Multi-threaded
 int i = 0;
 for(i = 0; i < NUMBER_OF_THREADS; i++) {
  sm.threadControls[i].runAgentDecision = 1; //The thread will turn it back to zero when done 
 }
 simulationManager_signalThreadsToGo(); //Thread is also expected to gather inputs
}
void simulationManager_runAgentActions() { //Single threaded
 int i;
  //printf("Did nothing to run agent actions\n");
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].energy > 0) {
   agent_performDecidedAction(sm.w.agents + i);
  }
  else {
   agent_kill(sm.w.agents + i);
  }
 }
}

void simulationManager_runIntelligenceTests() {
 intelligenceTestsResults res;
 intelTest_staticAnalysis(&res);
 intelTests_printResults(&res);
}

#endif
