#ifndef simulationmonitor_c
#define simulationmonitor_c
#include <stdio.h>
#include "simulationMonitor.h"
extern simulationManager sm;
void simulationMonitor_emitMonitors() {
 int i, c;
 float aveE;
 FILE *outFile;
 //Gather the stats to output 
 c = 0;
 aveE = 0;
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].energy > 0) {
   c++; 
   aveE += sm.w.agents[i].energy;
  }
 }
 //Output the file
 if(sm.smon.whichFileToUse == 'a')
  outFile = fopen(MONITOR_FILE_LOC_B,"w");
 else
  outFile = fopen(MONITOR_FILE_LOC_A,"w");
 fprintf(outFile,"agents:%i\niterations:%i\naveE:%f\nspeed:%f\nspeedD:%f\nspeedA:%f\nspeedS:%f\n",c,sm.i,aveE/(float)c,sm.smon.speed,sm.smon.speedDecision,sm.smon.speedAction,sm.smon.speedSeed);
 fprintf(outFile,"moves:%i\nturns:%i\nattacks:%i\ngrows:%i\nreplications:%i\n",sm.smon.moves,sm.smon.turns,sm.smon.attacks,sm.smon.grows,sm.smon.replications);
 fprintf(outFile,"killedBySeed:%i\n",sm.smon.killedBySeeding);
 fclose(outFile);
 //Close the right monitor 
 outFile = fopen(MONITOR_WHICH_FILE_TO_USE_FILE_LOC,"w");
 if(sm.smon.whichFileToUse == 'a'){
  sm.smon.whichFileToUse = 'b';
  fprintf(outFile,"b");
 }
 else {
  sm.smon.whichFileToUse = 'a';
  fprintf(outFile,"a");
 }
 fclose(outFile); 
}
void simulationMonitor_clear() {
 sm.smon.moves = 0;
 sm.smon.turns = 0;
 sm.smon.attacks = 0;
 sm.smon.grows = 0;
 sm.smon.replications = 0;
 sm.smon.killedBySeeding = 0; 
}
#endif
