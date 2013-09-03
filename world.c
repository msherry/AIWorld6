#ifndef world_c
#define world_c
#include <stdlib.h>
#include "world.h"

void world_makeRandomTerrain(world *w);
void world_createFromScratch(world *w)
{
 int x,y;
 w->worldSize = WORLD_SIZE;
 w->numbAgents = AG_TOTAL_ALLOWED;
 for(x = 0; x < w->worldSize; x++) { 
   for(y = 0; y < w->worldSize; y++) {
     w->agentInUse[x*w->worldSize+y] = 0;
     w->locs[x][y].a = NULL;
   } 
 }
 world_makeRandomTerrain(w);
}

void world_makeRandomTerrain(world *w)
{
 int x,y;
 for(x = 0; x < w->worldSize; x++) {
   for(y = 0; y < w->worldSize; y++) {
     w->locs[x][y].f = rand() / (float)RAND_MAX;
     w->locs[x][y].p = rand() / (float)RAND_MAX * 2.0;
   } 
 }
}

char *world_toString(world *w)
{
 printf("did nothing to save world\n");
 return "none";
}
void world_fromString(world *w, char *st)
{
 printf("did nothing to load the world\n");
}
#endif
