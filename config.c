#define NUMBER_OF_THREADS 4
#define WORLD_SIZE 100
#define WORLD_ITERATIONS 100
#define SEED_INTERVAL 10
#define SEED_DURATION 1000 
 
#define AG_TOTAL_ALLOWED 10000
//Outputs from the brain
#define AG_OUTPUTS 13
#define AG_OUTPUTS_DECISIONS 10
#define AG_M_F 0 
#define AG_M_L 1
#define AG_M_R 2
#define AG_T_L 3
#define AG_T_R 4
#define AG_A_F 5
#define AG_A_L 6
#define AG_A_R 7
#define AG_GROW 8
#define AG_SIGNAL 9
#define AG_SIGNAL_NUMB 2
#define AG_MEM 0
#define AG_MEM_NUMB 0
//Remmber, total options is 0-based

//Inputs to the brain
//  -----> Y axis
//|  0  1  2  3  4
//|  5  6  7  8  9  --Agent is at location 7
//v 10 11 12 13 14
//  15 16 17 18 19
//x 20 21 22 23 24
#define AG_INPUTS 125
#define AG_INPUT_TYPE_SIZE 25
#define AG_IN_FOOD  0
#define AG_IN_PASS  25
#define AG_IN_AGENE 50
#define AG_IN_SIGNAL 75

#define AG_INPUT_MAX 0xFF
//#define AG_INPUT_MIN -- No inputs are possible to be lower numbers
#define AG_MULT_MAX 0x7F
#define AG_MULT_MIN -0x7F

#define AG_MID_NODES 100
#define AG_CONNS 1000
#define AG_CONN_END 5
#define AG_CONN_IN 0
#define AG_CONN_MID 1
#define AG_INT_CONVERSION 0xFFFF
