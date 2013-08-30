#ifndef INTELLIGENCETESTS_C
#define INTELLIGENCETESTS_C
#include "simulationManager.h"
void intelTest_existAndLive(simulationManager *sm);
void intelTest_liveInToughPlaces(simulationManager *sm);
void intelTest_similarDNA(simulationManager *sm);
void intelTest_doObviouslyStupidThings(simulationManager *sm);
void intelTest_surviveNewEnvironment(simulationManager *sm);
void intelTest_survivePredator(simulationManager *sm);
void intelTest_surviveBetterTogether(simulationManager *sm);

void runAllTests(simulationManager *sm)
{
 char *worldString;
 worldString = world_toString(sm->w);
 intelTest_existAndLive(sm);
 world_fromString(sm->w,worldString);
 intelTest_liveInToughPlaces(sm);
 world_fromString(sm->w,worldString);
 intelTest_similarDNA(sm);
 world_fromString(sm->w,worldString);
 intelTest_doObviouslyStupidThings(sm);
 world_fromString(sm->w,worldString);
 intelTest_surviveNewEnvironment(sm);
 world_fromString(sm->w,worldString);
 intelTest_survivePredator(sm);
 world_fromString(sm->w,worldString);
 intelTest_surviveBetterTogether(sm);
 world_fromString(sm->w,worldString);
}
void intelTest_existAndLive(simulationManager *sm)
{;
}
void intelTest_liveInToughPlaces(simulationManager *sm)
{;
}
void intelTest_similarDNA(simulationManager *sm)
{;
}
void intelTest_doObviouslyStupidThings(simulationManager *sm)
{;
}
void intelTest_surviveNewEnvironment(simulationManager *sm)
{;
}
void intelTest_survivePredator(simulationManager *sm)
{;
}
void intelTest_surviveBetterTogether(simulationManager *sm)
{;
}
#endif
