#ifndef agent_h
#define agent_h
#include "brain.h"
typedef struct agent
{
 int nextDecision;
 int xLoc,yLoc; //Agent's location
 int facingDirection; //Agent's facing direction
 float signals[AG_SIGNAL_NUMB];
 float energy; 
 brain br;
} agent; 

void agent_makeDecision(agent *ag);
#endif
