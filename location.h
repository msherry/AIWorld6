#ifndef location_h
#define location_h

typedef struct location
{
 agent* a;
 float f; //Food level
 float p; //Passability - More specifically, the cost to traverse (any negative is impassible)
  
} location; 

#endif
