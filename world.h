#ifndef world_h
#define world_h

#include "location.h"
#include "agent.h"
typedef struct world
{
 int worldSize;
 int numbAgents;
 agent agents[AG_TOTAL_ALLOWED];
 location locs[WORLD_SIZE][WORLD_SIZE];

} world; 

void world_setupAgentList(world *w);
agent* world_mallocAgent(world *w);
void world_deleteAgent(world *w, agent *a);

#endif
