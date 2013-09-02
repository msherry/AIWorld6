#ifndef INTELLIGENCETESTS_C
#define INTELLIGENCETESTS_C
#include "simulationManager.h"
#include "intelligenceTestsResults.h"
void intelTest_staticAnalysis(intelligenceTestsResults *res);
void intelTest_doObviouslyStupidThings(intelligenceTestsResults *res);
void intelTest_surviveNewEnvironment(intelligenceTestsResults *res);
void intelTest_survivePredator(intelligenceTestsResults *res);
void intelTest_surviveBetterTogether(intelligenceTestsResults *res);
extern simulationManager sm;
void runAllTests(intelligenceTestsResults *res)
{
 char *worldString;
 worldString = world_toString(&(sm.w));
 intelTest_staticAnalysis(res);
 world_fromString(&(sm.w),worldString);
 intelTest_doObviouslyStupidThings(res);
 world_fromString(&(sm.w),worldString);
 intelTest_surviveNewEnvironment(res);
 world_fromString(&(sm.w),worldString);
 intelTest_survivePredator(res);
 world_fromString(&(sm.w),worldString);
 intelTest_surviveBetterTogether(res);
 world_fromString(&(sm.w),worldString);
}
//This is used for sorting arrays, because qsort doesn't have a default compare function
int cmpfunc (const void * a, const void * b) {
  if(*(float*)a == *(float*)b )
    return 0;
  else
  {
    if(*(float*)a < *(float*)b )
      return -1;
   else
      return 1;
  }
}

void intelTest_staticAnalysis(intelligenceTestsResults *res)
{
 int i,j;
 int ws = sm.w.worldSize;
 float listOfEnergy[ws*ws];
 float listOfFood[ws*ws];
 float listOfAgentsFood[ws*ws];
 res->totalAgents = 0;
 for(i = 0; i < ws; i++) {
   for(j = 0; j < ws; j++) {
     //What is the food distribution on this world? (So we can compare to the the food distribution where they live) 
     listOfFood[i*ws + j] = sm.w.locs[i][j].f;
     if(sm.w.locs[i][j].a != NULL)
     {
       //How much energy do they have?
       listOfEnergy[res->totalAgents] = sm.w.locs[i][j].a->energy;
       //Are they living in all food areas or only some?
       listOfAgentsFood[res->totalAgents] = sm.w.locs[i][j].f;
       //How many are there?
       res->totalAgents++;
     }
     //---- Do they have similar DNA? ----
   }
 }
 qsort(listOfEnergy,res->totalAgents,sizeof(float),cmpfunc);
 res->energyDistribution[0] = listOfEnergy[0];
 res->energyDistribution[1] = listOfEnergy[res->totalAgents/4];
 res->energyDistribution[2] = listOfEnergy[res->totalAgents*2/4];
 res->energyDistribution[3] = listOfEnergy[res->totalAgents*3/4];
 res->energyDistribution[4] = listOfEnergy[res->totalAgents-1];
 qsort(listOfAgentsFood,res->totalAgents,sizeof(float),cmpfunc);
 qsort(listOfFood,ws*ws,sizeof(float),cmpfunc);
 res->agentFoodDistribution[0] = listOfAgentsFood[0];
 res->agentFoodDistribution[1] = listOfAgentsFood[res->totalAgents/4];
 res->agentFoodDistribution[2] = listOfAgentsFood[res->totalAgents*2/4];
 res->agentFoodDistribution[3] = listOfAgentsFood[res->totalAgents*3/4];
 res->agentFoodDistribution[4] = listOfAgentsFood[res->totalAgents-1];
 res->worldFoodDistribution[0] = listOfFood[0];
 res->worldFoodDistribution[1] = listOfFood[ws*ws/4];
 res->worldFoodDistribution[2] = listOfFood[ws*ws*2/4];
 res->worldFoodDistribution[3] = listOfFood[ws*ws*3/4];
 res->worldFoodDistribution[4] = listOfFood[ws*ws-1];
}
int intelTest_staticAnalysis_test()
{
 int i,j;
 intelligenceTestsResults res;
 agent ags[8];
 for(i = 0; i < 4; i++)
   for(j = 0; j < 4; j++)
     sm.w.locs[i][j].a = NULL; //Clear it in case other tests are using the same world, after all it has the same simulation manager
 ags[0].energy = 2.0;
 ags[1].energy = 4.0;
 ags[2].energy = 6.0;
 ags[4].energy = 8.0;
 ags[5].energy = 0.01;
 ags[6].energy = 0.02;
 ags[7].energy = 1.0;
 sm.w.worldSize = 4;//For the sake of time and simplicity, only check a little of it
 sm.w.locs[0][0].a = &ags[7];
 sm.w.locs[3][3].a = &ags[6];
 sm.w.locs[3][2].a = &ags[5];
 sm.w.locs[2][2].a = &ags[4];
 sm.w.locs[1][1].a = &ags[3];
 sm.w.locs[0][1].a = &ags[2];
 sm.w.locs[1][0].a = &ags[1];
 sm.w.locs[2][1].a = &ags[0];
 sm.w.locs[0][0].f = 10;
 sm.w.locs[0][1].f = 5;
 sm.w.locs[0][2].f = 10;
 sm.w.locs[0][3].f = 10;
 sm.w.locs[1][0].f = 4;
 sm.w.locs[1][1].f = 6;
 sm.w.locs[1][2].f = 10;
 sm.w.locs[1][3].f = 0;
 sm.w.locs[2][0].f = 0;
 sm.w.locs[2][1].f = 3;
 sm.w.locs[2][2].f = 7;
 sm.w.locs[2][3].f = 0;
 sm.w.locs[3][0].f = 0;
 sm.w.locs[3][1].f = 0;
 sm.w.locs[3][2].f = 8;
 sm.w.locs[3][3].f = 9;
 intelTest_staticAnalysis(&res);
 if(!(res.totalAgents == 8
   && res.energyDistribution[0] > -0.01 && res.energyDistribution[0] < 0.01
   && res.energyDistribution[1] > 0.019 && res.energyDistribution[1] < 0.021
   && res.energyDistribution[2] > 1.9   && res.energyDistribution[2] < 2.1
   && res.energyDistribution[3] > 5.9 && res.energyDistribution[3] < 6.1
   && res.energyDistribution[4] > 7.9 && res.energyDistribution[4] < 8.1)) {
   printf("Failed intelTests agents number and energy distribution\n");
   intelTests_printResults(&res);
   return 0;
 }
 if(!(res.worldFoodDistribution[0] > -0.01 && res.worldFoodDistribution[0] < 0.01 
      && res.worldFoodDistribution[1] > -0.01 && res.worldFoodDistribution[1] < 0.01 
      && res.worldFoodDistribution[2] > 5.99 && res.worldFoodDistribution[2] < 6.01
      && res.worldFoodDistribution[3] > -9.9 && res.worldFoodDistribution[3] < 10.1 
      && res.worldFoodDistribution[4] > -9.9 && res.worldFoodDistribution[4] < 10.1)) { 
   printf("Failed intelTests world and agent food distribution\n"); 
   intelTests_printResults(&res);
   return 0;
 }
 return 1;
}
void intelTest_doObviouslyStupidThings(intelligenceTestsResults *res)
{;
}
void intelTest_surviveNewEnvironment(intelligenceTestsResults *res)
{
 world_makeRandomTerrain(&(sm.w));
 simulationManager_runIterations(1000, 0, 0);
 intelTest_staticAnalysis(res);
}
void intelTest_survivePredator(intelligenceTestsResults *res)
{;
}
void intelTest_surviveBetterTogether(intelligenceTestsResults *res)
{;
}
#endif
