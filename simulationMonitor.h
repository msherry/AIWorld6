#ifndef simulationmonitor_h 
#define simulationmonitor_h 
#include "intelligenceTestsResults.h"

typedef struct simulationMonitor
{
 intelligenceTestsResults intelRes;
 int moves, turns, attacks, grows, replications;
 double speed, speedDecision, speedAction, speedSeed, speedIntelTests;
 int killedBySeeding, killedByAttacks, killedByStarving;
 char whichFileToUse;
} simulationMonitor; 

void simulationMonitor_emitMonitors();

#endif
