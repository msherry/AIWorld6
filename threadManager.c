#ifndef threadmanager_c
#define threadmanager_c

void initThread(simulationManager_thread_control *tc, pthread *t, void *start_routine)
{ //This must be called by the parent before the child starts up
 tc->initComplete = 0;
 tc->childHasThisLock = 'a';
 tc->parentHasThisLock = 'b'; 
 tc->subRoutine = start_routine;
 pthread_mutex_lock(&(tc->actionLockC));
 pthread_mutex_lock(&(tc->actionLockB));
 pthread_create(t, NULL, initChild, (void*)tc);
 while(tc->initComplete == 0)
  {;}//We need to make sure lock A is taken, but taking lock C doesn't matter.
}
void initChild(void *args)
{
 void *subRoutine;
 simulationManager_thread_control *tc;
 tc = (simulationManager_thread_control*)args;
 subRoutine = tc->subRoutine;
 pthread_mutex_lock(&(tc->actionLockA));//This child must take A before the parent can wait on it FIX ME!!!!!!!!!!
 tc->initComplete = 1; 
 pthread_mutex_lock(&(tc->actionLockC));//This child will actually wait on C
 subRoutine(tc);
}
void notifyChildOfWorkToDo(simulationManager_thread_control *tc)
{
 //pthread_mutex_lock(&(tc->mainLock));
 //I don't need a main mutex lock, because only the parent will ever modify 'thread has this lock'
 //And the locks themselves have been proven to logically prevent any deadlocking or too-early starts
 switch (tc->childHasThisLock)
 {
  case 'a':
    tc->childHasThisLock = 'c'; 
    pthread_mutex_unlock(&(tc->actionLockC));
    pthread_mutex_lock(&(tc->actionLockA));
    break;
  case 'b':
    tc->childHasThisLock = 'b';
    pthread_mutex_unlock(&(tc->actionLockA));
    pthread_mutex_lock(&(tc->actionLockB));
    break;
  case 'c':
    tc->childHasThisLock = 'a';
    pthread_mutex_unlock(&(tc->actionLockB));
    pthread_mutex_lock(&(tc->actionLockC));
    break;
 }
 //pthread_mutex_unlock(&(tc->mainLock)); 
}

void notifyParentOfWorkCompleted(simulationManager_thread_control tc)
{
 switch (tc->parentHasThisLock)
 {
  case 'a':
    tc->parentHasThisLock = 'c';
    pthread_mutex_unlock(&(tc->actionLockC));
    pthread_mutex_lock(&(tc->actionLockA));
    break;
  case 'b':
    tc->parentHasThisLock = 'b';
    pthread_mutex_unlock(&(tc->actionLockA));
    pthread_mutex_lock(&(tc->actionLockB));
    break;
  case 'c':
    tc->parentHasThisLock = 'a';
    pthread_mutex_unlock(&(tc->actionLockB));
    pthread_mutex_lock(&(tc->actionLockC));
    break;
 }
}

void threadManager_test_run(void* args)
{
 simulationManager_thread_control *tc;
 tc = (simulationManager_thread_control*)args;
 printf("worker: 2");
 notifyParentOfWorkCompleted(tc);
 printf("worker: 4");
 notifyParentOfWorkCompleted(tc);
 printf("worker: 6");
 notifyParentOfWorkCompleted(tc);
 printf("worker: 8");
 
}
int threadManager_test()
{
 pthread_t worker;
 simulationManager_thread_control tc;
 printf("parent: 1");
 initThread(&tc, &worker, threadManager_test_run);
 printf("parent: 3");
 notifyChildOfWorkToDo(tc);
 printf("parent: 5");
 notifyChildOfWorkToDo(tc);
 printf("parent: 7");
 notifyChildOfWorkToDo(tc);
 printf("parent: 9");
}
#endif
/*
X has\tX blocked\tY has\tY blocked\taction
c\tb\tb,a\t\tY gets a
c\tb\tb,a\t\tY does work
c\tb\ta\t\tY releases b
c\tb\ta\tc\tY gets c
c,b\t\ta\tc\tX gets b
c,b\t\ta\tc\tX does work
b\t\ta\tc\tX releases c
b\ta\ta\tc\tX gets a
b\ta\ta,c\t\tY gets c
b\ta\ta,c\t\tY does work
b\ta\tc\t\tY releases a
b\ta\tc\tb\tY gets b
b,a\t\tc\tb\tX gets a
b,a\t\tc\tb\tX does work
a\t\tc\tb\tX releases b
a\tc\tc\tb\tX gets c
a\tc\tc,b\t\tY gets b
a\tc\tc,b\t\tY does work
a\tc\tb\t\tY releases c
a\tc\tb\ta\tY gets a
a,c\t\tb\ta\tX gets c
a,c\t\tb\ta\tX does work
c\t\tb\ta\tX releases a
c\tb\tb\ta\tX gets b
c\tb\tb,a\t\tY gets a
*/
