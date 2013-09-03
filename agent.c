#ifndef agent_c
#define agent_c
#include <float.h>
#include <stdio.h>
#include "agent.h"
extern simulationManager sm;
void agent_gatherInputs(agent *ag) {
 int i,j,k;
 location *tmpLoc;
 for(i = 0; i < 5; i++) {
  for(j = 0; j < 5; j++) {
   tmpLoc = &(sm.w.locs[ag->xLoc-1+j][ag->yLoc-2+i]);
   ag->br.inputs[AG_IN_FOOD+i*5+j]  = tmpLoc->f*AG_INT_CONVERSION;  
   ag->br.inputs[AG_IN_PASS+i*5+j]  = tmpLoc->p*AG_INT_CONVERSION;  
   if(tmpLoc->a->energy/10 > AG_INPUT_MAX)//Special case check to make sure the energy number isn't over the limits of the math
     ag->br.inputs[AG_IN_AGENE+i*5+j] = AG_INPUT_MAX*AG_INT_CONVERSION;
   else
     ag->br.inputs[AG_IN_AGENE+i*5+j] = tmpLoc->a->energy/10*AG_INT_CONVERSION;  
   for(k = 0; k < AG_SIGNAL_NUMB; k++) {
    ag->br.inputs[AG_IN_SIGNAL+AG_INPUT_TYPE_SIZE*k+i*5+j] = tmpLoc->s[k]*AG_INT_CONVERSION;  
   }
  }
 }
}
void agent_makeDecision(agent *ag) {
 int i,decision;
 float maxValue = FLT_MIN;
 for(i = 0; i < AG_OUTPUTS_DECISIONS; i++) {
  if(maxValue < ag->br.outputs[i]) {
   maxValue = ag->br.outputs[i];
   ag->nextDecision = i; 
  }
 }
 for(i = 0; i < AG_SIGNAL_NUMB; i++) {
  ag->signals[i] = ag->br.outputs[AG_SIGNAL+i];
 }
}

int agent_test() {
 int i,j;
 world *w;
 w = &(sm.w);
 agent as[100];
 agent *a;
 for(i = 0; i < 7; i++) {
  for(j = 0; j < 7; j++) {
   w->locs[i][j].f = 10.0*(float)i+(float)j;
   w->locs[i][j].p = 100+10.0*(float)i+(float)j;
   
   w->locs[i][j].a = &(as[i*7+j]);
   w->locs[i][j].a->energy = 100000.0+10.0*(float)i+(float)j;
   w->locs[i][j].a->xLoc = i;
   w->locs[i][j].a->yLoc = j;
   w->locs[i][j].s[0] = 200.0+10.0*(float)i+(float)j;
   if(AG_SIGNAL_NUMB > 1)
    w->locs[i][j].s[1] = 100.0+10.0*(float)i+(float)j;
  }
 }
 a = w->locs[2][3].a; 
 agent_gatherInputs(a);
 //printf("%i %i %i",-0xFF,-0xFF*0x7F,-0x7FFF);
 for(i = 0; i < AG_INPUTS; i++) {
  if( a->br.inputs[i]/(float)AG_INT_CONVERSION < 0 ) {
    printf("Failed: Agent: The numbers on the input were too low, likely broken\n");
    return 0; //All values should be positive, which they may not be if the input is not handled correctly
  }
 }
 for(i = 0; i < 5; i++) { //Test some foods
   if(a->br.inputs[AG_IN_FOOD+5+i]/AG_INT_CONVERSION != i*10+12) {
     printf("Failed: Agent: food mapping to input was bad. wanted %i, got %i\n",i*10+12,a->br.inputs[AG_IN_FOOD+5+i]/AG_INT_CONVERSION);
     return 0;
  }
 }
 for(i = 0; i < 5; i++) { //Test some movements
   if(a->br.inputs[AG_IN_PASS+10+i]/AG_INT_CONVERSION != i*10+113) {
     printf("Failed: Agent: pass mapping to input was bad. wanted %i, got %i\n",i*10+113,a->br.inputs[AG_IN_PASS+10+i]/AG_INT_CONVERSION);
     return 0;
  }
 }
 for(i = 0; i < 5; i++) { //Test some energy
   if(a->br.inputs[AG_IN_AGENE+i]/AG_INT_CONVERSION != AG_INPUT_MAX) {
     printf("Failed: Agent: energy mapping to input was bad.\n");
     return 0;
  }
 }
 for(i = 0; i < 5; i++) { //Test some signal
   if(a->br.inputs[AG_IN_SIGNAL+i]/AG_INT_CONVERSION != i*10+211) {
     printf("Failed: Agent: signal mapping to input was bad.\n");
     return 0;
  }
 }
 if(AG_SIGNAL_NUMB > 1) {
 for(i = 0; i < 5; i++) { //Test some extra signal
   if(a->br.inputs[AG_IN_SIGNAL+AG_INPUT_TYPE_SIZE+i]/AG_INT_CONVERSION != i*10+111) {
     printf("Failed: Agent: signal mapping to input was bad. Wanted %i but got %i \n",i*10+311,a->br.inputs[AG_IN_SIGNAL+AG_INPUT_TYPE_SIZE+i]/AG_INT_CONVERSION);
     return 0;
  }
 }
 }
 /*
 printf("foods:");
 for(i = 1; i < 6; i++) {
  for(j = 1; j < 6; j++) {
   printf("\t%i,%i:%i",i,j,(int)w->locs[i][j].s[1]);
  }
  printf("\n"); 
 } 
 printf("\n"); 
 printf("Inputs:");
 for(i = 0; i < AG_INPUTS; i++) {
  printf("\t%i:%i",i,w->locs[2][3].a->br.inputs[i]/AG_INT_CONVERSION);
 } 
 printf("\n");*/
 return 1;
}
#endif
