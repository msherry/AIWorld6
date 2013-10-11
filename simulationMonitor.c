#ifndef simulationmonitor_c
#define simulationmonitor_c
#include <stdio.h>
#include "simulationMonitor.h"
extern simulationManager sm;
void simulationMonitor_emitMonitors() {
 int i, c, totalActions;
 float aveE;
 FILE *outFile;
 //Gather the stats to output 
 c = 0;
 aveE = 0;
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].status == AG_STATUS_ALIVE) {
   c++; 
   aveE += sm.w.agents[i].energy;
  }
 }
 //Output the file
 if(sm.smon.whichFileToUse == 'a')
  outFile = fopen(MONITOR_FILE_LOC_B,"w");
 else
  outFile = fopen(MONITOR_FILE_LOC_A,"w");
 fprintf(outFile,"agents:%i\niterations:%i\naveEnergy:%f\nspeed:%f\nspeedD:%f\nspeedA:%f\nspeedS:%f\n",c,sm.i,aveE/(float)c,sm.smon.speed,sm.smon.speedDecision,sm.smon.speedAction,sm.smon.speedSeed);
 totalActions = (sm.smon.moves+sm.smon.turns+sm.smon.attacks+sm.smon.grows+sm.smon.replications);
 fprintf(outFile,"moves:%f\nturns:%f\nattacks:%f\ngrows:%f\nreplications:%f\n",(float)sm.smon.moves/(float)totalActions,(float)sm.smon.turns/(float)totalActions,(float)sm.smon.attacks/(float)totalActions,(float)sm.smon.grows/(float)totalActions,(float)sm.smon.replications/(float)totalActions);
 fprintf(outFile,"killedBySeed:%i\nkilledByAttacks:%i\nkilledByStarving:%i\n",sm.smon.killedBySeeding,sm.smon.killedByAttacks,sm.smon.killedByStarving);
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
 sm.smon.killedByAttacks = 0;
 sm.smon.killedByStarving = 0;
}

void simulationMonitor_runIntelligenceTests() { //These are all simulations, the static analysis should be run continuously
 printf("Did nothing to run the intelligence tests\n");
}

//-----------
// TESTS
//-----------
int simulationMonitor_test() {
 return 0;
}
#endif
