#ifndef simulationManager_thread_c
#define simulationManager_thread_c
void *simulationManager_thread_run(void *ptr) {
 simulationManager_thread_control* tc = (simulationManager_thread_control*)ptr; 
 printf("No work done by sim manager yet");
 while(tc->done == 0)
 {
  if(tc->runAgentDecision == 1) {
  }
  else if (tc->runAgentAction == 1) {
  }
  notifyParentOfWorkCompleted(tc); //This will block 
 }
}

#endif
