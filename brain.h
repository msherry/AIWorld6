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
 float inputs[AG_INPUTS];
 float mids[AG_MID_NODES];
 float outputs[AG_OUTPUTS];
 //Connections
 int connsUsed;
 unsigned char lvl[AG_CONNS];
 unsigned char in[AG_CONNS];
 unsigned char out[AG_CONNS];
 float multiplier[AG_CONNS];
} brain; 

#endif
