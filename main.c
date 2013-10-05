
// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "simulationManager.h" //Includes Pthread.h
#include "agent.h"
#include "location.h"
#include "world.h"//includes location.h
simulationManager sm;
#include "quickSigmoid.c"
#include "world.c"
#include "threadManager.c"
#include "intelligenceTests.c"
#include "brain.c"
#include "agent.c"
#include "simulationManager.c"//includes simulationManager.h

void runTests();
void runSimulation();
int main(int argc, char** argv)
{
 quickSigmoid_init();
 if(argc != 2) //Assume we're running tests now
  runTests();
 else
  switch (argv[1][1])
  {
   case 't': //Run tests
    runTests();
    break;
   case 'r': //Run simulation
    runSimulation();
  }
}
//Having this top level class as external not only reduces how much we need to pass it around, it also prevents us from having to cross link it at the thread control class, which greatly reduces the #include fancy footwork
void runSimulation()
{
 printf("Running the simulation now!!!!!!!!\n");
 simulationManager_run(); 
}

void runTests()
{
 world *w;
 w = &(sm.w);
 if(threadManager_test() == 1)
   printf("Passed: Thread manager tests\n");
 else
   printf("Failed: Thread manager tests\n");
 if(intelTest_staticAnalysis_test() == 1)
   printf("Passed: Static analysis tests\n");
 else
   printf("Failed: Static analysis tests\n");
 if(simulationManager_thread_test() == 1)
   printf("Passed: Simulation Manager Thread tests\n");
 else
   printf("Failed: Simulation Manager Thread tests\n");
 if(brain_test() == 1)
   printf("Passed: Brain tests\n");
 else
   printf("Failed: Brain tests\n");
 if(agent_test() == 1)
   printf("Passed: Agent tests\n");
 else
   printf("Failed: Agent tests\n");
 if(world_test() == 1)
   printf("Passed: World tests\n");
 else
   printf("Failed: World tests\n");
}
