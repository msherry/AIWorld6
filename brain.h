#ifndef brain_h
#define brain_h
/*  STRUCTURE
lvl 1 : inputs
lvl 2 : mids
lvl 3 : outputs
*/
typedef struct brain
{
 //Values
 int inputs[AG_INPUTS]; //Multiply by AG_INT_CONVERSION to make these into ints on the way in
 int mids[AG_MID_NODES];
 int outputs[AG_OUTPUTS];
 //Connections
 int connsUsed;
 unsigned char lvl[AG_CONNS];
 unsigned char in[AG_CONNS];
 unsigned char out[AG_CONNS];
 float multiplier[AG_CONNS];
} brain; 

#endif
