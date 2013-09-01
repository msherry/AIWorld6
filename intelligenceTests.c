#ifndef INTELLIGENCETESTS_C
#define INTELLIGENCETESTS_C
#include "simulationManager.h"
#include "intelligenceTestsResults.h"
void intelTest_staticAnalysis(simulationManager *sm, intelligenceTestsResults *res);
void intelTest_doObviouslyStupidThings(simulationManager *sm, intelligenceTestsResults *res);
void intelTest_surviveNewEnvironment(simulationManager *sm, intelligenceTestsResults *res);
void intelTest_survivePredator(simulationManager *sm, intelligenceTestsResults *res);
void intelTest_surviveBetterTogether(simulationManager *sm, intelligenceTestsResults *res);

void runAllTests(simulationManager *sm, intelligenceTestsResults *res)
{
 char *worldString;
 worldString = world_toString(&(sm->w));
 intelTest_staticAnalysis(sm,res);
 world_fromString(&(sm->w),worldString);
 intelTest_doObviouslyStupidThings(sm,res);
 world_fromString(&(sm->w),worldString);
 intelTest_surviveNewEnvironment(sm,res);
 world_fromString(&(sm->w),worldString);
 intelTest_survivePredator(sm,res);
 world_fromString(&(sm->w),worldString);
 intelTest_surviveBetterTogether(sm,res);
 world_fromString(&(sm->w),worldString);
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

void intelTest_staticAnalysis(simulationManager *sm, intelligenceTestsResults *res)
{
 int i,j;
 int ws = sm->w.worldSize;
 float listOfEnergy[ws*ws];
 float listOfFood[ws*ws];
 float listOfAgentsFood[ws*ws];
 res->totalAgents = 0;
 for(i = 0; i < ws; i++) {
   for(j = 0; j < ws; j++) {
     //What is the food distribution on this world? (So we can compare to the the food distribution where they live) 
     listOfFood[i*ws + j] = sm->w.locs[i][j].f;
     if(sm->w.locs[i][j].a != NULL)
     {
       //How much energy do they have?
       listOfEnergy[res->totalAgents] = sm->w.locs[i][j].a->energy;
       //Are they living in all food areas or only some?
       listOfAgentsFood[res->totalAgents] = sm->w.locs[i][j].f;
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
 //printf("---Exist and live test---\n");
 //printf("  * %i agents, distribution of energy (25pct blocks): [%f-%f-%f-%f-%f]\n",res->totalAgents,res->energyDistribution[0],res->energyDistribution[1],res->energyDistribution[2],res->energyDistribution[3],res->energyDistribution[4]);
}
int intelTest_staticAnalysis_test()
{
 simulationManager sm;
 intelligenceTestsResults res;
 agent ags[8];
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
 intelTest_staticAnalysis(&sm, &res);
 if(res.totalAgents == 8
   && res.energyDistribution[0] > -0.01 && res.energyDistribution[0] < 0.01
   && res.energyDistribution[1] > 0.019 && res.energyDistribution[1] < 0.021
   && res.energyDistribution[2] > 1.9   && res.energyDistribution[2] < 2.1
   && res.energyDistribution[3] > 5.9 && res.energyDistribution[3] < 6.1
   && res.energyDistribution[4] > 7.9 && res.energyDistribution[4] < 8.1)
   return 1;
 else
   return 0;
}
void intelTest_doObviouslyStupidThings(simulationManager *sm, intelligenceTestsResults *res)
{;
}
void intelTest_surviveNewEnvironment(simulationManager *sm, intelligenceTestsResults *res)
{;
}
void intelTest_survivePredator(simulationManager *sm, intelligenceTestsResults *res)
{;
}
void intelTest_surviveBetterTogether(simulationManager *sm, intelligenceTestsResults *res)
{;
}
#endif
