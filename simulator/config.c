#define EXP_NO_COMMUNICATION

#define NUMBER_OF_THREADS 2
#define SIM_ITERATIONS 400000
#define SIM_REPORT_INTERVAL 1000
#define SIM_INTEL_TEST_INTERVAL 100000
#define SIM_SEED_INTERVAL 100
#define SIM_SEED_DURATION 100000
#define SIM_SEED_ENERGY 20
#define SIM_SEED_SIZE 30

#define AG_TOTAL_ALLOWED 10000
#define AG_MAX_BUFFER_NEEDED 50000
#define AG_STATUS_ALIVE 1
#define AG_STATUS_DEAD 0
#define AG_STATUS_END_OF_LIST -1
#define AG_NO_LOCATION -99
#define PASS_IMPASSIBLE_INIT -1
#define PASS_IMPASSIBLE -1
#define WORLD_BORDER 3
#define WORLD_SIZE 100

#define AG_MUTATION_RATE 0.01

#define WORLD_PASS_COST_MULT 0.1
#define WORLD_FOOD_MULT 1
#define AG_MAX_ENERGY 10000
#define AG_ATTACK_RATE 0.1
#define AG_ATTACK_EFF 0.5
#define AG_ATTACK_COST 1
#define AG_TURN_COST 0.1
#define AG_MOVE_COST 0.1
#define AG_GROW_RATE 1
#define AG_GROW_COST 0.1
#define AG_REPLICATION_COST 0.5
#define AG_REPLICATION_GIVE 0.3

//Outputs from the brain
#define AG_OUTPUTS 11
#define AG_OUTPUTS_DECISIONS 9
#define AG_M_F 0 
#define AG_M_L 1
#define AG_M_R 2
#define AG_T_L 3
#define AG_T_R 4
#define AG_A_F 5
#define AG_R   6
#define AG_R_F 7
#define AG_GROW 8
#define AG_SIGNAL 9
#define AG_SIGNAL_NUMB 3
#define AG_MEM 0
#define AG_MEM_NUMB 0
//Remmber, total options is 0-based

//Inputs to the brain - facing down
//  -----> Y axis
//|  0  1  2  3  4
//|  5  6  7  8  9  --Agent is at location 7
//v 10 11 12 13 14
//  15 16 17 18 19
//x 20 21 22 23 24
#define AG_INPUTS 125
#define AG_INPUT_TYPE_SIZE 25
#define AG_IN_RAND 0
#define AG_IN_FOOD 1
#define AG_IN_PASS 26
#define AG_IN_AGENE 51
#define AG_IN_SIGNAL 76

#define AG_INPUT_MAX 0xFF
//#define AG_INPUT_MIN -- No inputs are possible to be lower numbers
#define AG_MULT_MAX 0x7F
#define AG_MULT_MIN -0x7F
#define AG_MULT_INIT_RANGE 0x2F

#define AG_MID_NODES 100
#define AG_CONNS_INIT 90
#define AG_CONNS_L1 500
#define AG_CONNS_L2 500
#define AG_CONN_END 130
#define AG_INT_CONVERSION 0xFFFF

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define INTELTESTS_FILE_LOC "./data_from_simulations/intelTests.txt" 
#define MONITOR_FILE_LOC "./data_from_simulations/monitor.txt"
//The world files switch off between A and B in order to maintain consistency in case we kill the process in the middle of saving.
#define WORLD_AGENTS_FILE_LOC_A "./data_from_simulations/world_agents_a.txt"
#define WORLD_AGENTS_FILE_LOC_B "./data_from_simulations/world_agents_b.txt"
#define WORLD_LOCS_FILE_LOC_A "./data_from_simulations/world_locs_a.txt"
#define WORLD_LOCS_FILE_LOC_B "./data_from_simulations/world_locs_b.txt"
#define WORLD_WHICH_FILE_TO_USE_FILE_LOC "./data_from_simulations/world_whichFileToUse.txt"
