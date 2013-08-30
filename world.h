#ifndef world_h
#define world_h

#include "location.h"
#include "agent.h"
typedef struct world
{
 int worldSize;
 agent agents[WORLD_SIZE*WORLD_SIZE];
 int agentInUse[WORLD_SIZE*WORLD_SIZE];
 location locs[WORLD_SIZE][WORLD_SIZE];

} world; 

#endif
