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

void world_save(world *w)
{
 int i; 
 FILE *outFile;
 fopen(WORLD_FILE,"w");
 for(i = 0; i < w->numbAgents; i++) {
  ; //agent_save(outFile,w->agents + i);
 }
 fclose(outFile); 
}
void world_load(world *w)
{
 printf("did nothing to load the world\n");
}

void world_setupAgentList(world *w) {
 int i;
 for(i = 0; i < w->numbAgents; i++) {
  w->agents[i].id = i;
  w->agents[i].energy = -1;
 }
}
agent* world_mallocAgent(world *w) {
 int i,start;
 start = (int)((rand() / (float)RAND_MAX)*w->numbAgents);
 for(i = start; (i - start) < w->numbAgents; i++) {
  if(w->agents[i%w->numbAgents].energy <= 0) {
   return w->agents + (i%w->numbAgents);
  }
 }
}
void world_deleteAgent(world *w, agent* a) {
 printf("Don't need to delete, since this is what happens when their energy is too low\n");
}
#endif
