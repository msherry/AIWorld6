#ifndef simulationmonitor_c
#define simulationmonitor_c
#include <stdio.h>
#include "simulationMonitor.h"
extern simulationManager sm;
void simulationMonitor_emitMonitors() {
 int i, c;
 FILE *outFile;
 c = 0;
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].energy > 0)
   c++; 
 }
 outFile = fopen(MONITOR_FILE,"a");
 fprintf(outFile,"%i\n",c);
 fclose(outFile);
}
#endif
