#ifndef world_h
#define world_h

#include "location.h"

typedef struct world
{
 location** locs[WORLD_SIZE][WORLD_SIZE];

} world; 

#endif
