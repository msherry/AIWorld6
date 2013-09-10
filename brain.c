#ifndef brain_c
#define brain_c
#include "brain.h"

void brain_makeDecision(brain *br)
{
 int i;
 int *ins, *outs, *mids;
 float *multL1, *multL2;
 unsigned char *inL1, *outL1, *inL2, *outL2;
 ins = br->inputs; 
 mids = br->mids;
 outs = br->outputs;
 inL1 = br->inL1;
 outL1 = br->outL1;
 inL2 = br->inL2;
 outL2 = br->outL2;
 multL1 = br->multL1;
 multL2 = br->multL2;
 for(i = 0; i < AG_MID_NODES; i++) { //Reset the middle nodes to zero
  mids[i] = 0;
 } 
 i = 0;
 while(inL1[i] != AG_CONN_END) {
  mids[outL1[i]] += ins[inL1[i]] * multL1[i];
  i++;
 } //NOTE: The mutation script is expected to assure we don't have backward connections (mid to in, for exmaple)
 for(i = 0; i < AG_MID_NODES; i++) {
  mids[i] = quickSigmoid_Sigmoid(mids[i]); //NOTE: The mutation script needs to also assure the value doesn't exceed the maxes that the simoid function can handle
 }
 for(i = 0; i < AG_OUTPUTS; i++) {
  outs[i] = 0;
 } 
 i = 0;
 while(inL2[i] != AG_CONN_END) {
  outs[outL2[i]] += mids[inL2[i]] * multL2[i]; 
  i++;
 }
 //NOTE: Only need to apply sigmoid to the signals
 for(i = AG_SIGNAL; i < (AG_SIGNAL+AG_SIGNAL_NUMB); i++) {
  outs[i] = quickSigmoid_Sigmoid(outs[i])/(float)AG_INT_CONVERSION;
 }
}

//----------------------
// Replication: Seeding 
//----------------------
void brain_fillRestWithNoOps(unsigned char *in, unsigned char *out, int connMax, int i) {
 for( ; i < connMax && in[i] != AG_CONN_END; i++) {
 in[i] = AG_CONN_END;
 }
}
void brain_makeConnLvlFromScratch(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax);
void brain_makeFromScratch(brain *newB) {
 newB->mutationRate = AG_MUTATION_RATE;
 brain_makeConnLvlFromScratch(newB->inL1,AG_INPUTS,newB->outL1,AG_MID_NODES,newB->multL1,newB->mutationRate,AG_CONNS_L1);  
 brain_makeConnLvlFromScratch(newB->inL2,AG_MID_NODES,newB->outL2,AG_OUTPUTS,newB->multL2,newB->mutationRate,AG_CONNS_L2);  
}
void brain_makeConnLvlFromScratch(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax) {
 int i;
 for(i = 0; i < AG_CONNS_INIT; i++) {
  out[i] = rand() / (float)RAND_MAX * outMax;
  in[i] = rand() / (float)RAND_MAX * inMax;
  mult[i] = ((rand() / (float)RAND_MAX) -0.5) * AG_MULT_INIT_RANGE; 
 }
 brain_fillRestWithNoOps(in,out,connMax,i);
}
//----------------------
// Replication: Asexual
//----------------------
void brain_makeConnLvlFromAsex(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, unsigned char *oldIn, unsigned char *oldOut, float *oldMult);
void brain_considerMutatingConn(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, int i);
int brain_considerAddingAConn(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, int i);
void brain_makeFromAsex(brain *newB, brain *b) {
 newB->mutationRate = b->mutationRate;
 brain_makeConnLvlFromAsex(newB->inL1,AG_INPUTS,newB->outL1,AG_MID_NODES,newB->multL1,newB->mutationRate,AG_CONNS_L1,b->inL1,b->outL1,b->multL1); 
 brain_makeConnLvlFromAsex(newB->inL2,AG_MID_NODES,newB->outL2,AG_OUTPUTS,newB->multL2,newB->mutationRate,AG_CONNS_L2,b->inL2,b->outL2,b->multL2); 
}

void brain_makeConnLvlFromAsex(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, unsigned char *oldIn, unsigned char *oldOut, float *oldMult) {
 int i = 0;
 while(oldIn[i] != AG_CONN_END) {
  in[i] = oldIn[i];
  out[i] = oldOut[i];
  mult[i] = oldMult[i];
  brain_considerMutatingConn(in,inMax,out,outMax,mult,mutationRate,connMax,i);
  i++;
 } 
 i = brain_considerAddingAConn(in,inMax,out,outMax,mult,mutationRate,connMax,i);
 brain_fillRestWithNoOps(in,out,connMax,i);
}
void brain_considerMutatingConn(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, int i) { //Make sure the connections don't exceed the max
 if(rand() / (float)RAND_MAX < mutationRate) { //Mod a connection
  mult[i] = (1+mutationRate)*mult[i]; 
  if(mult[i] > AG_MULT_MAX) {
   mult[i] = AG_MULT_MAX; 
  }
 }
 if(rand() / (float)RAND_MAX < mutationRate) { //Mod a connection
  mult[i] = (1-mutationRate)*mult[i]; 
  if(mult[i] < AG_MULT_MIN) {
   mult[i] = AG_MULT_MIN; 
  }
 }
 if(rand() / (float)RAND_MAX < mutationRate *0.1) { //delete the connection
  mult[i] == 0; 
  if(in[i+1] == AG_CONN_END) { //This is the last, delete it
   in[i] = AG_CONN_END;
  }
 }
}

int brain_considerAddingAConn(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, int i) {
 if(rand() / (float)RAND_MAX < mutationRate *0.1 && i < (connMax+1)) { //Add a connection
  out[i] = rand() / (float)RAND_MAX * outMax;
  in[i] = rand() / (float)RAND_MAX * inMax;
  mult[i] = ((rand() / (float)RAND_MAX) -0.5) * AG_MULT_INIT_RANGE;
  i++;
 }
 return i;
}
//---------------------
// Replication: Sexual
//---------------------
void brain_makeConnLvlFromSex(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, unsigned char *oldInA, unsigned char *oldOutA, float *oldMultA, unsigned char *oldInB, unsigned char *oldOutB, float *oldMultB);
void brain_makeFromSex(brain *newB, brain *b, brain *c) {
 newB->mutationRate = b->mutationRate;
 brain_makeConnLvlFromSex(newB->inL1,AG_INPUTS,newB->outL1,AG_MID_NODES,newB->multL1,newB->mutationRate,AG_CONNS_L1,b->inL1,b->outL1,b->multL1,c->inL1,c->outL1,c->multL1); 
 brain_makeConnLvlFromSex(newB->inL2,AG_MID_NODES,newB->outL2,AG_OUTPUTS,newB->multL2,newB->mutationRate,AG_CONNS_L2,b->inL2,b->outL2,b->multL2,c->inL2,c->outL2,c->multL2); 
}
void brain_makeConnLvlFromSex(unsigned char *in, unsigned char inMax, unsigned char *out, unsigned char outMax, float *mult, float mutationRate, int connMax, unsigned char *oldInA, unsigned char *oldOutA, float *oldMultA, unsigned char *oldInB, unsigned char *oldOutB, float *oldMultB) {
 int i = 0;
 while(oldInA[i] != AG_CONN_END || oldInB[i] != AG_CONN_END) {
  if(i%2 == 0 && oldInA[i] != AG_CONN_END) { //Alternate which creature we take the data from
   in[i] = oldInA[i];
   out[i] = oldOutA[i];
   mult[i] = oldMultA[i];
  } 
  if(i%2 == 1 && oldInB[i] != AG_CONN_END) {
   in[i] = oldInB[i];
   out[i] = oldOutB[i];
   mult[i] = oldMultB[i];
  }
  brain_considerMutatingConn(in,inMax,out,outMax,mult,mutationRate,connMax,i);
  i++;
 }
 i = brain_considerAddingAConn(in,inMax,out,outMax,mult,mutationRate,connMax,i);
 brain_fillRestWithNoOps(in,out,connMax,i);
}
//---------
// Testing 
//---------
int brain_test() {
 if (brain_test_makeDecision() == 0)
  return 0; 
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
 //normal con
 br.inL1[0] = 0;
 br.outL1[0] = 2;
 br.multL1[0] = 1; 
 //normal con2
 br.inL1[1] = 2;
 br.outL1[1] = 2;
 br.multL1[1] = -1;
 //limit con
 br.inL1[2] = 1;
 br.outL1[2] = 0;
 br.multL1[2] = 1;
 //limit multiplier con
 br.inL1[3] = 3;
 br.outL1[3] = 1;
 br.multL1[3] = 2;
 br.inL1[4] = AG_CONN_END;
 //normal con
 br.inL2[0] = 2;
 br.outL2[0] = 1;
 br.multL2[0] = 1.0;
 //limit con
 br.inL2[1] = 0;
 br.outL2[1] = 0;
 br.multL2[1] = 1.0;
 //limit mult con
 br.inL2[2] = 1;
 br.outL2[2] = 2;
 br.multL2[2] = 1.0;
 br.inL2[3] = AG_CONN_END;
 brain_makeDecision(&br);
 //printf("input over limit %f\n",br.outputs[0]/(float)AG_INT_CONVERSION);
 //printf("mult over limit %f\n",br.outputs[2]/(float)AG_INT_CONVERSION);
 o = br.outputs[1]/(float)AG_INT_CONVERSION; 
 if(o > 0.7615 && o < 0.7616)
   return 1;
 return 0;
}
#endif
