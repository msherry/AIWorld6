#ifndef brain_c
#define brain_c
#include "brain.h"
void brain_makeDecision(brain *br)
{
 int i,j;
 float *ins,outs,mids,multiplier;
 char* in,out,lvl;
 ins = br->inputs; 
 mids = br->mids;
 outs = br->outputs;
 in = br->in;
 out = br->out;
 lvl = br->lvl;
 multiplier = br->multiplier;
 while(lvl[i] == AG_CONN_IN) {
  mids[out[i]] = ins[in[i]] * multiplier[i];
  i++;
 } //NOTE: The mutation script is expected to assure we don't have backward connections (mid to in, for exmaple)
 for(j = 0; j < AG_MID_NODES; j++) {
  mids[j] = quickSigmoid_Sigmoid[mids[j]];
 } 
 while(lvl[i] == AG_CONN_MID) {
  outs[out[i]] = mids[in[i]] * multiplier[i]; 
 }
 //NOTE: Only need to apply sigmoid to the signals
 for(j = AG_SIGNAL; j < (AG_SIGNAL+AG_SIGNAL_NUMB); j++)
  outs[j] = quickSigmoid_Sigmoid[outs[j]];
}

#endif
