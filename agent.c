#ifndef agent_c
#define agent_c
#include <float.h>
#include "agent.h"
void agent_makeDecision(agent *ag)
{
 int i,decision;
 float maxValue = FLT_MIN;
 for(i = 0; i < AG_OUTPUTS_DECISIONS; i++) {
  if(maxValue < ag->br.outputs[i]) {
   maxValue = ag->br.outputs[i];
   ag->nextDecision = i; 
  }
 }
 for(i = 0; i < AG_SIGNAL_NUMB; i++) {
  ag->signals[i] = ag->br.outputs[AG_SIGNAL+i];
 }
}

#endif
