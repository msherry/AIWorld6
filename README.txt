TODO:
* Agents are not getting killed when seeding. I suspct they're not being removed down to zero energy...
* Fix the way files and rendering is done (we're getting half finished files)
* Add terrain??
* Fix all these seg-faults. I suspect they're related to the change in killing agents so an agent can be NULL

-----------------------------------
PROJECT MANAGEMENT
-----------------------------------
* Intelligence tests - DONE
* Threading organization - DONE
* Brain - Setup inputs - DONE
* Brain - Run output - DONE
* Brain - Replicate - DONE
* Agent actions
* Fix world's edges and agent creation so agents can't go there
* Seeing functions
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
* Location - Attributes of that locations, including the creature pointer * SimulationManager - Lists of threads, syncs threads as needed, runs iterations on the world, calls to get metrics. Threads stripe the world and thus must be synced.  * AgentManager - List of all agents, get and release the memory needed for them * Agent

IMPLEMENTAION: Agent function
* The world has to chang just enough to prevent long-term stagnation. Changing climate? Are we going to stick with the 'you must be alone to grow' concept? it does force long-term thought and movement past eachother... what are the alternatives? 
* Allow agents to stack up - They can't all get energy from the same spot, but they can at least slide past eachother. 

IMPLEMENTATION: Tests for intelligence
How can you tell if something is intelligent?
 * [ANALYSIS] They do exist and live
 * [ANALYSIS] They live in all the places that living is *possible* (not just easy)
 * [SIMULATION] They don't do obviously stupid things - waste energy on moves with no-outcome (we need to have a no-op move)
 * [ANALYSIS] They have the same approach to a similar situation, they will have similar brain structure (the same way living things on earth mostly look the same). 
 * [SIMULATION] Given a new environment, can they survive
 * [SIMULATION] Given a varacious predator, can they survive
 * [SIMULATION] Do they survive better spread out or lumped together
 ??* They save up and then expend in a big way, and can do this in patterns

This should be more like 'things I'd like to prove' - that these complexities benefit them
* Move and attack vs. move-attack
* Move-only vs. move-attack
* Changing climate
* Take a set of agents from an evolved world, place them randomly on a new world vs. place them togethe on a new world
* Give them language...Given 1 hormone vs.0 vs. 5, how do agents perform? (do they benefit from having more, or even no conversation?)
* Give them memory
* Give them the ability to modify the environment

IMPLEMENTATION: Agent senses
* Can see food values (0 to 1 - Value you get from eating here)
* Can see passibility values (0 to 1 - Cost of moving here (other creatures are a 2, and actually impassible))
* Can see log of other agents' energy (0 to inifinity)
* Can see 'hormone' values[triple pair] (-1 to 1)
 ---  3
----- 5
----- 5
--a-- 5
----- 5
23 inputs per type, 6 types = h

IMPLEMENTATION: Agent actions
* hormone set
* decision
** grow (no other agents nearby)
** move forward
** move left
** move right
** move back
** turn left
** turn right
** attack forward
** attack left
** attack right 

