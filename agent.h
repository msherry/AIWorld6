#ifndef agent_h
#define agent_h

typedef struct agent
{
 int i;
 float energy; 
} agent; 

void agent_makeDecision(agent *ag);
#endif
