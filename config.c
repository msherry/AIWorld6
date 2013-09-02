#define NUMBER_OF_THREADS 4
#define WORLD_SIZE 100
#define WORLD_ITERATIONS 100
#define SEED_INTERVAL 10
#define SEED_DURATION 1000 
 

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
#define AG_SIGNAL_NUMB 3
#define AG_MEM 0
#define AG_MEM_NUMB 0
//Remmber, total options is 0-based

//Inputs to the brain
#define AG_INPUTS 138
#define AG_INPUT_TYPE_SIZE 23
#define AG_IN_FOOD  0
#define AG_IN_PASS  23
#define AG_IN_AGENE 46
#define AG_IN_SIGNAL 69
//92 115 138
//The signal number applies here too, just multiplied by 23

#define AG_MID_NODES 100
#define AG_CONNS 1000
#define AG_CONN_END 5
#define AG_CONN_IN 0
#define AG_CONN_MID 1
