-----------------------------------
DESIGN
-----------------------------------
SIMULATION GOALS:
* Evolve sexual reproduction
* Evolve cooperative behavior / multi-cellular behavior

IMPEMENTATION GOALS:
* Avoid the world stagnation problem
* Allocate all memory at the beginning
* Multi-threading in the C itself

IMPLEMENTATION: Classes
* Main - Runs the simulation, runs the tests, runs the display system, allows options for debug, timing, etc
* World - 2D array of locations, can save and load itself
* Location - Attributes of that locations, including the creature pointer
* SimulationManager - Lists of threads, syncs threads as needed, runs iterations on the world, calls to get metrics. Threads stripe the world and thus must be synced.
* AgentManager - List of all agents, get and release the memory needed for them 
* Agent

IMPLEMENTAION: Agent function
* The world has to chang just enough to prevent long-term stagnation. Changing climate? Are we going to stick with the 'you must be alone to grow' concept? it does force long-term thought and movement past eachother... what are the alternatives? 
* Allow agents to stack up - They can't all get energy from the same spot, but they can at least slide past eachother. 


This actually isn't about the agents. THis is about measuing the outcome. What defines a successful outcome? Intelligence level. How can you tell if something is intelligent?
 - Individual intelligence -
* Many of them agree. THey have the same approach, they will have similar brain structure (the same way living things on earth mostly look the same). 
* They don't do obviously stupid things - waste energy on moves with no-outcome (we need to have a no-op move)
* They do exist and live
* They live in all the places that living is *possible* (not just easy)
* They save up and then expend in a big way, and can do this in patterns
* Given a new environment, can they survive
 - Social intelligence - 
* Survive the introduction of a varacious predator
* The world alone test 

Tests
* Move and attack vs. move-attack
* Move-only vs. move-attack
* Changing climate
* Give them language 
* Take a set of agents from an evolved world, place them randomly on a new world vs. place them together on a new world
