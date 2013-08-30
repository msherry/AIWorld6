#ifndef simulationManager_thread_c
#define simulationManager_thread_c
void *simulationManager_thread_run(void *ptr) {
 simulationManager_thread_control* control = (simulationManager_thread_control*)ptr; 
 while(control->done == 0)
 {
  pthread_mutex_lock(&(control->actionLock));//Wait for work
  control->runAgentAction = 0;
  control->runAgentDecision = 0;
  pthread_mutex_unlock(&(control->actionLock));//Work completed
 }  
}

#endif
