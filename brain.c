#ifndef brain_c
#define brain_c
#include "brain.h"
void brain_makeDecision(brain *br)
{
 int i,j;
 int *ins, *outs, *mids;
 float *multiplier;
 char *in, *out, *lvl;
 ins = br->inputs; 
 mids = br->mids;
 outs = br->outputs;
 in = br->in;
 out = br->out;
 lvl = br->lvl;
 multiplier = br->multiplier;
 for(j = 0; j < AG_MID_NODES; j++) {
  mids[j] = 0;
 } 
 i = 0;
 while(lvl[i] == AG_CONN_IN) {
  mids[out[i]] += ins[in[i]] * multiplier[i];
  i++;
 } //NOTE: The mutation script is expected to assure we don't have backward connections (mid to in, for exmaple)
 for(j = 0; j < AG_MID_NODES; j++) {
  mids[j] = quickSigmoid_Sigmoid(mids[j]);
 } 
 for(j = 0; j < AG_OUTPUTS; j++) {
  outs[j] = 0;
 } 
 while(lvl[i] == AG_CONN_MID) {
  outs[out[i]] += mids[in[i]] * multiplier[i]; 
  i++;
 }
 //NOTE: Only need to apply sigmoid to the signals
 for(j = AG_SIGNAL; j < (AG_SIGNAL+AG_SIGNAL_NUMB); j++) {
  outs[j] = quickSigmoid_Sigmoid(outs[j])/(float)AG_INT_CONVERSION;
 }
}
int brain_test()
{
 float o;
 brain br;
 br.inputs[0] = 1.0*AG_INT_CONVERSION;
 br.inputs[1] = 2.0*AG_INT_CONVERSION;
 br.inputs[2] = -1.0*AG_INT_CONVERSION;
 br.lvl[0] = AG_CONN_IN;
 br.in[0] = 0;
 br.out[0] = 2;
 br.multiplier[0] = 1;
 br.lvl[1] = AG_CONN_IN;
 br.in[1] = 2;
 br.out[1] = 2;
 br.multiplier[1] = -1;
 br.lvl[2] = AG_CONN_MID;
 br.in[2] = 2;
 br.out[2] = 1;//This is the final output
 br.multiplier[2] = 1.0;
 br.lvl[3] = AG_CONN_END;
 brain_makeDecision(&br);
 o = br.outputs[1]/(float)AG_INT_CONVERSION; 
 if(o > 0.7615 && o < 0.7616)
   return 1;
 return 0;
}
#endif
