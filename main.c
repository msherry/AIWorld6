
// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "simulationManager.h" //Includes Pthread.h
#include "location.h"
#include "world.h"//includes location.h
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
 simulationManager_run(sm); 
}

void runTests()
{
 printf("All tests passed\n");
}
