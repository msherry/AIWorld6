#ifndef agent_h
#define agent_h
#include "brain.h"
typedef struct agent
{
 int nextDecision;
 float signals[AG_SIGNAL_NUMB];
 float energy; 
 brain br;
} agent; 

void agent_makeDecision(agent *ag);
#endif
