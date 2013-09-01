#ifndef intelligencetestsresults_h 
#define intelligencetestsresults_h 

typedef struct intelligenceTestsResults
{
 int totalAgents;
 float energyDistribution[5];
 float worldFoodDistribution[5];
 float agentFoodDistribution[5];
} intelligenceTestsResults;

intelTests_printResults(intelligenceTestsResults *res)
{
 printf("---Exist and live test---\n");
 printf("  * %i agents, distribution of energy (25pct blocks): [%f-%f-%f-%f-%f]\n",res->totalAgents,res->energyDistribution[0],res->energyDistribution[1],res->energyDistribution[2],res->energyDistribution[3],res->energyDistribution[4]);
 printf("---Food locations test---\n");
 printf("  All food: [%f-%f-%f-%f-%f] agent food locations: [%f-%f-%f-%f-%f]\n",res->worldFoodDistribution[0],res->worldFoodDistribution[1],res->worldFoodDistribution[2],res->worldFoodDistribution[3],res->worldFoodDistribution[4],res->agentFoodDistribution[0],res->agentFoodDistribution[1],res->agentFoodDistribution[2],res->agentFoodDistribution[3],res->agentFoodDistribution[4]);
}

#endif

