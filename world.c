#ifndef world_c
#define world_c
#include <stdio.h>
#include <stdlib.h>
#include "world.h"

void world_makeRandomTerrain(world *w);
void world_createFromScratch(world *w)
{
 int x,y;
 w->worldSize = WORLD_SIZE;
 w->worldBorder = WORLD_BORDER;
 w->numbAgents = AG_TOTAL_ALLOWED;
 for(x = 0; x < w->worldSize; x++) { 
   for(y = 0; y < w->worldSize; y++) {
     w->locs[x][y].a = NULL;
   } 
 }
 world_makeRandomTerrain(w);
 world_setupAgentList(w);
}

void world_makeRandomTerrain(world *w)
{
 int x,y;
 for(x = 0; x < w->worldSize; x++) {
  for(y = 0; y < w->worldSize; y++) {
   w->locs[x][y].f = rand() / (float)RAND_MAX;
   w->locs[x][y].p = rand() / (float)RAND_MAX * 2.0;
   if(x < w->worldBorder || y < w->worldBorder || x >= (w->worldSize - w->worldBorder) || y >= (w->worldSize - w->worldBorder)) {
    w->locs[x][y].p = PASS_IMPASSIBLE;
   }
  } 
 }
}
void world_save_toAOrB(world *w, char aOrB) {
 int i; 
 FILE *outFile;
 printf("Saving the world\n");
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
 if(aOrB == 'a')
  inFile = fopen(WORLD_FILE_LOC_A,"r");
 else
  inFile = fopen(WORLD_FILE_LOC_B,"r");
 while(fgets(str,AG_MAX_BUFFER_NEEDED,inFile) != NULL) {
  agent_load(str,AG_MAX_BUFFER_NEEDED);  
 } 
 printf("did nothing to load the world\n");
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
  
 return 0;
}
#endif
