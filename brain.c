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

void brain_makeFromScratch(brain *newB) {
 int i;
 for(i = 0; i < AG_CONNS_INIT/2; i++) {
  newB->lvl[i] = AG_CONN_IN;
  newB->out[i] = rand() / (float)RAND_MAX * AG_MID_NODES;
  newB->in[i] = rand() / (float)RAND_MAX * AG_INPUTS;
 }
 for(i = AG_CONNS_INIT/2; i < AG_CONNS_INIT; i++) {
  newB->lvl[i] = AG_CONN_MID;
  newB->out[i] = rand() / (float)RAND_MAX * AG_OUTPUTS;
  newB->in[i] = rand() / (float)RAND_MAX * AG_MID_NODES;
 }
 newB->lvl[i] = AG_CONN_END;
}

void brain_makeFromAsex(brain *newB, brain *b) {
 printf("Did nothing to make the a-sex brain\n");
}

void brain_makeFromSex(brain *newB, brain *b, brain *c) {
 printf("Did nothing to make the brain have sex\n");
}

int brain_test() {
 if (brain_test_makeDecision() == 0)
  return 0;
 else 
  return 1;
}

int brain_test_makeDecision()
{
 float o;
 brain br;
 br.inputs[0] = 1.0*AG_INT_CONVERSION;
 //Inputs over the limit are no longer possible, the mult will be below a number and the input will be below a number
 br.inputs[1] = 0;//(0x7FFF+2)*AG_INT_CONVERSION;//This should be rtight over the limit
 br.inputs[2] = -1.0*AG_INT_CONVERSION;
 br.inputs[3] = 0;//(0x7FFF)*AG_INT_CONVERSION;//This should be at the limit, but will be multiplied
 br.lvl[0] = AG_CONN_IN; //normal con
 br.in[0] = 0;
 br.out[0] = 2;
 br.multiplier[0] = 1; 
 br.lvl[1] = AG_CONN_IN;//normal con2
 br.in[1] = 2;
 br.out[1] = 2;
 br.multiplier[1] = -1;
 br.lvl[2] = AG_CONN_IN; //limit con
 br.in[2] = 1;
 br.out[2] = 0;
 br.multiplier[2] = 1;
 br.lvl[3] = AG_CONN_IN;//limit multiplier con
 br.in[3] = 3;
 br.out[3] = 1;
 br.multiplier[3] = 2;
 br.lvl[4] = AG_CONN_MID;//normal con
 br.in[4] = 2;
 br.out[4] = 1;
 br.multiplier[4] = 1.0;
 br.lvl[5] = AG_CONN_MID;//limit con
 br.in[5] = 0;
 br.out[5] = 0;
 br.multiplier[5] = 1.0;
 br.lvl[6] = AG_CONN_MID;//limit mult con
 br.in[6] = 1;
 br.out[6] = 2;
 br.multiplier[6] = 1.0;

 br.lvl[7] = AG_CONN_END;
 brain_makeDecision(&br);
 //printf("input over limit %f\n",br.outputs[0]/(float)AG_INT_CONVERSION);
 //printf("mult over limit %f\n",br.outputs[2]/(float)AG_INT_CONVERSION);
 o = br.outputs[1]/(float)AG_INT_CONVERSION; 
 if(o > 0.7615 && o < 0.7616)
   return 1;
 return 0;
}
#endif
