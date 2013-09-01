#ifndef simulationmanager_thread_info
#define simulationmanager_thread_info
typedef void (*functiontype)();

typedef struct simulationManager_thread_control
{
 int childNumber;
 volatile int runAgentDecision;
 volatile int runAgentAction;
 volatile int done;
 pthread_mutex_t actionLockA, actionLockB, actionLockC;
 char childHasThisLock, parentHasThisLock;
 volatile int initComplete;
 functiontype subRoutine;
} simulationManager_thread_control;
#endif
