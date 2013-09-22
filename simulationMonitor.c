#ifndef simulationmonitor_c
#define simulationmonitor_c
#include <stdio.h>
#include "simulationMonitor.h"
extern simulationManager sm;
void simulationMonitor_emitMonitors() {
 int i, c;
 float aveE;
 FILE *outFile;
 c = 0;
 aveE = 0;
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].energy > 0) {
   c++; 
   aveE += sm.w.agents[i].energy;
  }
 }
 outFile = fopen(MONITOR_FILE,"w");
 fprintf(outFile,"agents:%i\niterations:%i\naveE:%f\nspeed:%f\nspeedD:%f\nspeedA:%f\nspeedS:%f\n",c,sm.i,aveE/(float)c,sm.speed,sm.speedDecision,sm.speedAction,sm.speedSeed);
 fclose(outFile);
}
#endif
