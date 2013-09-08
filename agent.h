#ifndef agent_h
#define agent_h
#include "brain.h"
typedef struct agent
{
 int nextDecision;
 int xLoc,yLoc; //Agent's location
 int id; //The location in the overall agent array, used only by world
 int facingDirection; //Agent's facing direction
 float signals[AG_SIGNAL_NUMB];
 float energy; 
 brain br;
} agent; 

void agent_makeDecision(agent *ag);
#endif
