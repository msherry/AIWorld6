
// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "simulationManager.h" //Includes Pthread.h
#include "agent.h"
#include "location.h"
#include "world.h"//includes location.h
#include "world.c"
#include "threadManager.c"
#include "intelligenceTests.c"
#include "simulationManager.c"//includes simulationManager.h
void runTests();
void runSimulation();
int main(int argc, char** argv)
{
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

void runSimulation()
{
 simulationManager sm;
 simulationManager_run(&sm); 
}

void runTests()
{
 if(threadManager_test() == 1)
   printf("Passed: Thread manager tests\n");
 else
   printf("Failed: Thread manager tests\n");
}
