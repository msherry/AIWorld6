#ifndef world_c
#define world_c
#include <stdio.h>
#include <stdlib.h>
#include "world.h"

void world_makeRandomTerrain(world *w);
void world_clear(world *w);
void world_createFromScratch(world *w)
{
 world_clear(w);
 world_makeRandomTerrain(w);
}

void world_clear(world *w) {
 int x,y;
 w->worldSize = WORLD_SIZE;
 w->worldBorder = WORLD_BORDER;
 w->numbAgents = AG_TOTAL_ALLOWED;
 for(x = 0; x < w->worldSize; x++) { 
   for(y = 0; y < w->worldSize; y++) {
     w->locs[x][y].a = NULL;
   } 
 }
 world_setupAgentList(w);
}
void world_makeRandomTerrain(world *w)
{
 int x,y;
 for(x = 0; x < w->worldSize; x++) {
  for(y = 0; y < w->worldSize; y++) {
   w->locs[x][y].f = rand() / (float)RAND_MAX * WORLD_FOOD_MULT;
   w->locs[x][y].p = rand() / (float)RAND_MAX * WORLD_PASS_COST_MULT;
   if(x < w->worldBorder || y < w->worldBorder || x >= (w->worldSize - w->worldBorder) || y >= (w->worldSize - w->worldBorder)) {
    w->locs[x][y].p = PASS_IMPASSIBLE;
   }
  } 
 }
}
void world_save_toAOrB(world *w, char aOrB) {
 int i; 
 FILE *outFile;
 if(aOrB == 'a') //We have two files and switch between them so the reader can read a compete file in real time.
  outFile = fopen(WORLD_FILE_LOC_A,"w");
 else
  outFile = fopen(WORLD_FILE_LOC_B,"w");
 for(i = 0; i < w->numbAgents && w->agents[i].status != AG_STATUS_END_OF_LIST; i++) {
  if(w->agents[i].status == AG_STATUS_ALIVE > 0) {
   agent_save(w->agents + i, outFile);
  }
 }
 fclose(outFile); 
}
void world_save(world *w) {
 int i; 
 FILE *outFile;
 if(w->whichFileToUse == 'a') //We have two files and switch between them so the reader can read a compete file in real time.
  world_save_toAOrB(w,'b');
 else
  world_save_toAOrB(w,'a');
 //Now set the next state
 outFile = fopen(WORLD_WHICH_FILE_TO_USE_FILE_LOC, "w");
 if(w->whichFileToUse == 'a'){ 
  fprintf(outFile,"b");
  w->whichFileToUse = 'b';
 }
 else {
  fprintf(outFile,"a");
  w->whichFileToUse = 'a';
 }
 fclose(outFile);
}
void world_load(world *w, char aOrB)
{
 FILE *inFile;
 char str[AG_MAX_BUFFER_NEEDED];
 world_clear(w);
 if(aOrB == 'a')
  inFile = fopen(WORLD_FILE_LOC_A,"r");
 else
  inFile = fopen(WORLD_FILE_LOC_B,"r");
 while(fgets(str,AG_MAX_BUFFER_NEEDED,inFile) != NULL) {
  agent_load(str,AG_MAX_BUFFER_NEEDED);  
 } 
 fclose(inFile);
}

void world_setupAgentList(world *w) {
 int i;
 for(i = 0; i < w->numbAgents; i++) {
  w->agents[i].status = AG_STATUS_END_OF_LIST; 
  //w->agents[i].id = i;
  //w->agents[i].energy = -1;
 }
}
agent* world_mallocAgent(world *w,int x,int y) {
 int i; //always start at zero, anything after that one is a null.
 if(w->locs[x][y].a != NULL) {
  printf("You tried to allocate an agent on an occupied space?! %i %i\n",x,y);
  return NULL; 
 }
 for(i = 0; i < w->numbAgents; i++) {
  if(w->agents[i].status == AG_STATUS_DEAD || w->agents[i].status == AG_STATUS_END_OF_LIST) {
   w->agents[i].status = AG_STATUS_ALIVE;
   w->agents[i].xLoc = x;
   w->agents[i].yLoc = y;
   w->locs[x][y].a = w->agents + i;
   return w->agents + i;
  }
 }
 return NULL;
}
void world_deleteAgent(world *w, agent* a) {
 w->locs[a->xLoc][a->yLoc].a = NULL;
 a->xLoc = AG_NO_LOCATION;
 a->yLoc = AG_NO_LOCATION;
 a->status = AG_STATUS_DEAD;
}

//----------
// TESTS
//----------
int world_test() {
 agent *ag; 
 int br_inL1_3, br_outL1_2;
 float br_multL2_0;
 world_createFromScratch(&(sm.w)); 
 agent_mallocAgent_fromScratch(5,7,10); 
 ag = sm.w.locs[5][7].a;
 br_inL1_3 = ag->br.inL1[3];
 br_outL1_2 = ag->br.outL1[2];
 br_multL2_0 = ag->br.multL2[0];
 agent_mallocAgent_fromScratch(10,11,100); 
 world_save_toAOrB(&sm.w,'a');
 world_createFromScratch(&(sm.w)); //I now expect it to be empty again
 if(sm.w.locs[5][7].a != NULL || sm.w.locs[10][11].a != NULL) {
  printf("World test: Agents were still there after a create-from-scratch.\n"); 
  return 0;
 }
 agent_mallocAgent_fromScratch(2,3,10); 
 agent_mallocAgent_fromScratch(4,5,100); 
 world_save_toAOrB(&sm.w,'b');
 world_load(&sm.w,'a');
 if(sm.w.locs[2][3].a != NULL || sm.w.locs[4][5].a != NULL) {
  printf("World test: Agents were still there after a load.\n"); 
  return 0;
 }
 ag = sm.w.locs[5][7].a;
 if(ag == NULL) {
  printf("World test: I failed to find the agent I wanted \n");
  return 0;
 }
 if(ag->br.inL1[3] != br_inL1_3 || ag->br.outL1[2] != br_outL1_2 || ag->br.multL2[0] < br_multL2_0 - 0.001 ||ag->br.multL2[0] > br_multL2_0 + 0.001) { 
  printf("World test: Agents didn't have the values expected. Wanted %i %i %f, got %i %i %f\n",br_inL1_3,br_outL1_2,br_multL2_0,ag->br.inL1[3],ag->br.outL1[2],ag->br.multL2[0]); 
  return 0;
 }
 //Also, what about clearing the old agents in memory in the world??
 return 1;
}
#endif
