#ifndef simulationmanager_thread_info
#define simulationmanager_thread_info
typedef struct simulationManager_thread_control
{
 int runAgentDecision;
 int runAgentAction;
 int done;
 pthread_mutex_t actionLockA, actionLockB, actionLockC;
 char threadHasThisLock, parentHasThisLock;
 volatile int initComplete;
 void *subRoutine;
} simulationManager_thread_control;
#endif
