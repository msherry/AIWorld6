#ifndef simulationmonitor_h 
#define simulationmonitor_h 
typedef struct simulationMonitor
{
 int moves, turns, attacks, grows, replications;
 double speed, speedDecision, speedAction, speedSeed;
 int killedBySeeding;
 char whichFileToUse;
} simulationMonitor; 

void simulationMonitor_emitMonitors();

#endif
