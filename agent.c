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
     ag->br.inputs[AG_IN_AGENE+i*5+j] = tmpLoc->a->energy/20*AG_INT_CONVERSION;  //Energy is reduced cuz its a big number ususally
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

agent* agent_mallocAgent(int x, int y, float e) {
 agent *a;
 a = world_mallocAgent(&(sm.w)); 
 a->xLoc = x;
 a->yLoc = y;
 a->energy = e;
 a->facingDirection = UP; 
 return a;
}
void agent_mallocAgent_fromScratch(int x, int y, float e) {
 agent *a; 
 if(sm.w.locs[x][y].a != NULL)//Kill the agent if this one lands on them
   sm.w.locs[x][y].a->energy = -1;//The general assumption is any agent with negative energy is dead
 a = agent_mallocAgent(x,y,e);
 brain_makeFromScratch(&(a->br));
}
agent* agent_mallocAgent_checkAndMake(agent *a) {
 agent *newA; 
 int i,j,x,y;
 float e;
 newA = NULL;
 x = -1; //Look for a location nearby to put this agent in
 for(i = -1; i < 2; i++) {
  for(j = -1; j < 2; j++) {
   if(sm.w.locs[a->xLoc+i][a->yLoc+j].a->energy < 0 && sm.w.locs[a->xLoc+i][a->yLoc+j].p > PASS_IMPASSIBLE) {
    x = a->xLoc+i;
    y = a->yLoc+j; 
   } 
  }
 }  
 if( x > 0 ) { //We did find a location to put it in 
  e = a->energy/AG_REPLICATION_GIVE;
  a->energy -= e - AG_REPLICATION_COST; //The cost of replication
  newA = agent_mallocAgent(x,y,e);
 }
 return newA;
}
void agent_mallocAgent_fromAsex(agent *a) {
 agent *newA = agent_mallocAgent_checkAndMake(a);
 if(newA != NULL)
  brain_makeFromAsex(&(newA->br),&(a->br));
}
void agent_mallocAgent_fromSex(agent *a, agent *b) {
 agent *newA = agent_mallocAgent_checkAndMake(a);
 if(newA != NULL)
  brain_makeFromSex(&(newA->br),&(a->br),&(b->br));
}

int agent_test_mallocs();
int agent_test_gatherInputs();
int agent_test() {
 if(agent_test_gatherInputs() == 0)
    return 0;
 if(agent_test_mallocs() == 0) {
  printf("Failed: Agent mallocs\n");
  return 0; 
 }
 return 1;
}

int agent_test_mallocs() {
 int i;
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].energy > 0) {
   return 0; //No agents shoud have anything yet   
  } 
 } 
 for(i = 0; i < sm.w.numbAgents; i++) {
  agent_mallocAgent_fromScratch(i%sm.w.worldSize, (int)(i/sm.w.worldSize), 10);  
 }
 for(i = 0; i < sm.w.numbAgents; i++) {
  if(sm.w.agents[i].energy < 0) {
   return 0; //All agents should have things
  }
 } 
 return 1;
}

int agent_test_gatherInputs() {
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
